
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

struct transaction{
   float low;
   float high;
   long long dailycaps;
};


int main(int argc, char* argv[])
{	
	map<int, map<string, map<string, transaction> > > map_query;
	map<int, map<string, map<string, transaction> > > map_cap;
	map<int, map<string, map<string, transaction> > >::iterator iter;
	//map<int, map<string, map<string, transaction> > >::reverse_iterator iter_r;
    /*read file*/
    ifstream fin(argv[1]);//public_data.txt
    string line;

    int date;
    string currency, exchange, trash; 
    float low, high;
    long long dailycaps;

    while(getline(fin, line)){
        istringstream in (line);
        in >> date; 
        getline(in, trash, '\t');
        getline(in, currency, '\t');
        getline(in, exchange, '\t');
        in >> low >> high >> dailycaps;
        map_query[date][currency][exchange].low=low;
        map_query[date][currency][exchange].high=high;
        map_query[date][currency][exchange].dailycaps=dailycaps;
		map_cap[date][exchange][currency].dailycaps=dailycaps;
    }
    fin.close();
    
    
		
    map<string, map<string, transaction> >::iterator iter_1;
    map<string, transaction>::iterator iter_2;
	string command,extrema;
	cin >> command;
	int flag_query=0;
	int flag_price=0;
	int flag_cap=0;
	while(command!="end")//?
    {
        if (command=="query"){
		/*
		if (flag_query==0){
			
			flag_query++;
		}
		*/
	        cin >> date >> currency >> exchange;

    		iter=map_query.find(date);
	        if (iter==map_query.end())
	        	printf("none\n");
		else{
    			iter_1=(iter->second).find(currency);
			if (iter_1==(iter->second).end())
				printf("none\n");
			else{
    				iter_2=(iter_1->second).find(exchange);
				if (iter_2==(iter_1->second).end())
					printf("none\n");
				else
	        			printf("%.4f %.4f %lld\n",(iter_2->second).low,\
					(iter_2->second).high,(iter_2->second).dailycaps);
			}
		}
		
	}
	
	if (command=="price"){
		/*
		if(flag_price==0){
			
			flag_price++;
		}
		*/
	        cin >> extrema >> date >> currency;

    		iter=map_query.find(date);
	        if (iter==map_query.end())
	        	printf("none\n");
		else{
    			iter_1=(iter->second).find(currency);
			if (iter_1==(iter->second).end())
				printf("none\n");
			else{
				if(extrema=="min"){
				float lowest=((iter_1->second).begin()->second).low;
    				for(iter_2=(iter_1->second).begin(); iter_2!=(iter_1->second).end(); iter_2++)
					{if((iter_2->second).low<lowest)
						lowest=(iter_2->second).low;}
	        			printf("%.4f\n",lowest);
				}
				if(extrema=="max"){
				float highest=((iter_1->second).begin()->second).high;
    				for(iter_2=(iter_1->second).begin(); iter_2!=(iter_1->second).end(); iter_2++)
					{if((iter_2->second).high>highest)
						highest=(iter_2->second).high;}
	        			printf("%.4f\n",highest);
				}
			}
		}
	}
	
	if (command=="cap"){
		/*
		if (flag_cap==0){
			
			flag_cap++;
		}
		*/
	        cin >> date >> exchange;

    		iter=map_cap.find(date);
	        if (iter==map_cap.end())
	        	printf("none\n");
		else{
    			iter_1=(iter->second).find(exchange);
			if (iter_1==(iter->second).end())
				printf("none\n");
			else{
				long long sum=0;
    				for(iter_2=(iter_1->second).begin(); iter_2!=(iter_1->second).end(); iter_2++)
					sum=sum+(iter_2->second).dailycaps;
					//printf("%lld\n",(iter_2->second).dailycaps);
	        		printf("%lld\n",sum);
			}
		}
	}
	
        cin >> command;//query,price,cap
    }
    
    return 0;
}

