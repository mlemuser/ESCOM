#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	long int num_sprinklers, distance_to_cover, width;
	int flag, flag_modify, complete;

	while(cin >> num_sprinklers >> distance_to_cover >> width)
	{
		vector<pair<double, double> > ranges;
		int minimum_sprinklers = 0;

		pair<int, int> sprinkler;
		pair<double, double> generate_range, aux2;
		double distance_range, actual_mark = 0.0, best_range_taken = 0.0;

		for(long int i = 0; i < num_sprinklers; i++)
		{
			cin >> sprinkler.first >> sprinkler.second;

			if((sprinkler.second * 2) > width)
			{
				distance_range = (sqrt((4 * pow(sprinkler.second, 2)) - (pow(width, 2)))) / (2);
				generate_range.first = sprinkler.first - distance_range;
				generate_range.second = sprinkler.first + distance_range;
				
				ranges.push_back(generate_range);
			}
			
		}

		//--------------------------------------------------------

		while(actual_mark < distance_to_cover)
		{
			
			flag = 0;
			complete = 1;
			flag_modify = 0;

			for(int j = 0; j < ranges.size(); j++)
			{
				
				if(ranges[j].first <= actual_mark)
				{
					if(ranges[j].second > actual_mark)
					{
						flag = 1;
						if((ranges[j].second - actual_mark) > best_range_taken)
						{
							
							aux2.first = ranges[j].first;
							aux2.second = ranges[j].second;
							
							best_range_taken = ranges[j].second - actual_mark;
							flag_modify = 1;
						}
					}
					
				}
			}

			if(flag == 0)
			{
				cout << "-1" << endl;
				complete = 0;
				break;
			}

			if(flag_modify == 1)
			{
				minimum_sprinklers++;
				actual_mark = actual_mark + best_range_taken;
				best_range_taken = 0.0;
			}
			
		}

		if(complete == 1)
			cout << minimum_sprinklers << endl;
	}


	return 0;
}
