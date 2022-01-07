#include<ncurses.h>
#include<unistd.h>

int year=2022;

int main(){
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();

	clear();

	char*week="mo tu we th fr sa su";
	char*names[12]={"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
	char mlens[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	// XXX the following two will have to be updated every century
	if(year%4)mlens[1]--; // leap
	int moffset=(year+year/4+5)%7; // first day of year

	for(int x=0;x<4;x++)
	for(int y=0;y<3;y++){
		int m=x*3+y; // month index
		// the upper left corner of each month is at (x*8,y*22)
		// iow each month is 8 chars tall (name + week + 5*digits + spacing)
		//  and 22 chars wide (7*(2*digits+spacing) + spacing)
		mvaddstr(x*8,y*22+9,names[m]); // name offset by 9 to be centered above month
		mvaddstr(x*8+1,y*22,week); // x+1 for next line
		for(int i=1;i<mlens[m]+1;i++){
			// offsets for the following follow from the above, plus some offset for each day
			// i is day of month, moffset is the offset of the first day (eg if its a wednesday,
			//   we start at the third place)
			if(i>9) // if two digits
			mvaddch(
				(i+moffset)/7+8*x+2,
				((i+moffset)%7)*3+22*y, // *3 for two digits + spacing
			i/10+'0');

			mvaddch(
				(i+moffset)/7+8*x+2,
				((i+moffset)%7)*3+22*y+1, // +1 bc second digit
			i%10+'0');
		}

		// update offset
		moffset=(moffset+mlens[m])%7;
	}

	refresh();

	while(getch()!='q')usleep(1000);

	endwin();
}
