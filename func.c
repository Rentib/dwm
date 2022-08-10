/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */
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
