//ccw->1, cw->-1
int ccw(int a1, int b1, int a2, int b2, int a3, int b3)
{
	int ret=(a2-a1)*(b3-b2)-(a3-a2)*(b2-b1);
	if(ret==0) return 0;
	if(ret>0) return 1
	if(ret<0) return -1;
}
