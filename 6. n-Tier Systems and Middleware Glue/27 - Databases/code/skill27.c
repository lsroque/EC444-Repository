/* Author: Lesbeth Roque
Skill 26 - State Machines
2020-11-10
Team 15
*/

// Psuedocode for wack-a-mole game
init(){
	int points = 0; //keep track of score
	new timer event timer; //initialize timer
	int game_start = 1; //flag to check if game is running
	int hit;

}

int mole show(){
	object mole = new mole; //create a new mole
	int mole_pos = rand(); // place mole in a random position
	return mole_pos;
}

void no_mole_show(mole_pos){ //use mole_pos to find mole
	delete(mole); // make mole "disappear"
}

void main(){
	if (game_start == 1){ //game started
		start timer;
		mole_show();
		if(hit == 1) {
			points +=10; //increment score
			no_mole_show();
			if(timerstillrunnning){
				mole_show();
			}
			else{
				game_start = 0; // timer has eneded, game is over
			}
		}
	}
	else {
		no_mole_show();
	}
}