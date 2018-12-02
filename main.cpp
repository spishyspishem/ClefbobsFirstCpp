#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main()
{
	srand(time(NULL));
	
	const int STARTING_HEALTH = 20;
	const int MAX_HEALTH  = 20;
	const int STARTING_ENERGY = 0;
	const int MAX_ENERGY  = 20;
	const int MAX_NUM_PLAYERS = 2;
	
	int play_again = 1;
	
	do
	{
	  int p_health[MAX_NUM_PLAYERS];
	  int p_energy[MAX_NUM_PLAYERS];
	  for(int i = 0; i < MAX_NUM_PLAYERS; i++)
	  {
	  	p_health[i] = STARTING_HEALTH;
	    p_energy[i] = STARTING_ENERGY;
	  }
	  
	  int turn_num = 0;
	  bool game_over = false;
	  
	  do
	  {
	  	int user_input;
	  	int target;
	  	int rand_num = rand()%(6-1 + 1) + 1;
	  	int active_player = turn_num % MAX_NUM_PLAYERS;
	  	
	  	// display a divider for each turn
	  	std::cout << "-------------------- It's turn " << turn_num+1 << " --------------------";
	  	
	  	// display all player info for this turn
	  	for(int i = 0; i < MAX_NUM_PLAYERS; i++)
 	    {
 	      std::cout << "\n\nPlayer " << i+1 << " health: (" << p_health[i] << ")\t";
	      for(int j = 0; j < p_health[i]; j++)
	      {
	      	std::cout << "_";
		    }
		    std::cout << "\nPlayer " << i+1 << " energy: (" << p_energy[i] << ")\t";
	      for(int j = 0; j < p_energy[i]; j++)
	      {
	      	std::cout << "_";
		    }
	    }
	    std::cout << "\n\nIt's Player " << active_player+1 << "'s turn!\n\n";
	  	
	  	// display prompts
	  	std::cout << "Enter left (1), up (2), right (3) or down (4) to charge, x (5) to attack, and y (6) to heal:\nYou entered: ";
	  	std::cin  >> user_input;
	  	if(user_input == 5)
	  	{
	  	  std::cout << "Now enter your target (player number).\n";
	  	  std::cin  >> target;
	    }
	    
	    // respond to user-entered button commands
		  if(user_input == 1 || user_input == 2 || user_input == 3 || user_input == 4)
	  	{
	  	  std::cout << "\nYou rolled a " << rand_num << "!\n";
	  		if(rand_num % user_input == 0 || rand_num == 1)
	  		{
	  			p_energy[active_player] += user_input;
	  		}
	  		else
	  		{
	  			p_energy[active_player] -= user_input;
	  		}
	  		
	  		// make sure to keep  the energy in the correct limits
	      if(p_energy[active_player] < 0)	{p_energy[active_player] = 0; }
	  		if(p_energy[active_player] > MAX_ENERGY) {p_energy[active_player] = MAX_ENERGY; }
		  }
		  if(user_input == 5)
		  {
		    p_health[target - 1] -= p_energy[active_player];
		    p_energy[active_player] = 0;
		  }
      if(user_input == 6)
      {
        p_health[active_player] += round(static_cast<float>(p_energy[active_player])/2);
        p_energy[active_player] = 0;
      }
		  if(p_health[active_player] < 0)	{p_health[active_player] = 0; }
		  if(p_health[active_player] > MAX_HEALTH)	{p_health[active_player] = MAX_HEALTH; }
		  
		  // determine if anybody is dead
		  for(int i = 0; i < MAX_NUM_PLAYERS; i++)
		  {
		  	if(p_health[i] == 0)
		  	{
		  		game_over = true;
		  	}
		  }
		
	  	turn_num++;
	  }
	  while(!game_over);
	  std::cout << "\nAnd that's the game! The winner is Player " << ((turn_num - 1) % MAX_NUM_PLAYERS)+1 
              << "!\n\nWould you like to play again? (1 for Yes, 2 for No): ";
	  std::cin  >> play_again;
	  std::cout << "\n\n";
  }
  while(play_again == 1);
	return 0;
}
