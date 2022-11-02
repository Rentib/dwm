void changetheme(const Arg *arg);
void movestack(const Arg *arg);
void shiftview(const Arg *arg);
void toggleborder(const Arg *arg);
void togglefullscr(const Arg *arg);

void
changetheme(const Arg *arg)
{
  unsigned int i, j;
  defaultcolorscheme = (defaultcolorscheme + 1) % ColorSchemeLast;

  for (i = 0; i < LENGTH(colors); i++)
    for (j = 0; j < 3; j++)
      colors[i][j] = colorscheme[defaultcolorscheme][i][j];

  for (i = 0; i < LENGTH(colors); i++)
    free(scheme[i]);

	scheme[LENGTH(colors)] = drw_scm_create(drw, colors[0], 3);
	for (i = 0; i < LENGTH(colors); i++)
		scheme[i] = drw_scm_create(drw, colors[i], 3);

  drawbars();
}

/** Function to push selected client up/down the stack */
void
movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i > 0) {
    c = nexttiled(selmon->sel->next);
		if(!c)
      c = nexttiled(selmon->clients);
	}
	else {
		for(i = selmon->clients; i != selmon->sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for (; i; i = i->next)
				if (!i->isfloating && ISVISIBLE(i))
					c = i;
	}
	/* find the client before selmon->sel and c */
	for(i = selmon->clients; i && (!p || !pc); i = i->next) {
		if(i->next == selmon->sel)
			p = i;
		if(i->next == c)
			pc = i;
	}

	/* swap c and selmon->sel selmon->clients in the selmon->clients list */
	if(c && c != selmon->sel) {
		Client *temp = selmon->sel->next==c?selmon->sel:selmon->sel->next;
		selmon->sel->next = c->next==selmon->sel?c:c->next;
		c->next = temp;

		if(p && p != c)
			p->next = c;
		if(pc && pc != selmon->sel)
			pc->next = selmon->sel;

		if(selmon->sel == selmon->clients)
			selmon->clients = c;
		else if(c == selmon->clients)
			selmon->clients = selmon->sel;

		arrange(selmon);
	}
}

/** Function to shift the current view to the left/right */
void
shiftview(const Arg *arg)
{
	Arg shifted;

	if(arg->i > 0) // left circular shift
		shifted.ui = (selmon->tagset[selmon->seltags] << arg->i)
		   | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - arg->i));

	else // right circular shift
		shifted.ui = selmon->tagset[selmon->seltags] >> (- arg->i)
		   | selmon->tagset[selmon->seltags] << (LENGTH(tags) + arg->i);

	view(&shifted);
}

/** Function to toggle selected client's fullscreen */
void
togglefullscr(const Arg *arg)
{
  if (selmon->sel)
    setfullscreen(selmon->sel, !selmon->sel->isfullscreen);
}

/** Function to toggle border of selected client */
void
toggleborder(const Arg *arg)
{
  if (selmon && selmon->sel) {
    selmon->sel->bw = (selmon->sel->bw == borderpx ? 0 : borderpx);
    arrange(selmon);
  }
}
