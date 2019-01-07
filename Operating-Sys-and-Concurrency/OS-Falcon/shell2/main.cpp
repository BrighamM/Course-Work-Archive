#include <iostream> 
#include <algorithm>
#include <string.h>
#include <vector>
#include <sys/types.h>
#include <stdio.h>
#include <cctype>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>


// Some clerical corrections were made by searching the internet for solutions

/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
been altered and appended to by me Brigham Michaelis
*/
char* convert(const std::string &toConvert)
{
	char* c = new char[toConvert.size() + 1];
	strcpy(c, toConvert.c_str());
	return c;
}

/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
been altered and appended to by me Brigham Michaelis
*/
std::vector<std::string> stringToVector(const std::string &userInput)
{
	std::vector<std::string> words;
	auto curr = userInput.begin();
	while(std::distance(curr,userInput.end()) >= 0)
	{
		auto next = std::find(curr,userInput.end(),' ');
		words.emplace_back(curr,next);
		curr = next;
		++curr;
	}
	return words;
}

/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
been altered and appended to by me Brigham Michaelis
*/
std::vector<char*> sVectToCVect(const std::vector<std::string> &words)
{
	std::vector<char*> args;
	std::transform(words.begin(),words.end(),std::back_inserter(args), convert);
	args.push_back(nullptr);
	return args;
}

/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
been altered and appended to by me Brigham Michaelis
*/
void printStringVector(const std::vector<std::string> &words)
{
	for(auto&& v:words)
	{
		std::cout<< v << std::endl;
	}
}

/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
been altered and appended to by me Brigham Michaelis
*/
void printCharVector(const std::vector<char*> &args)
{
	std::cout<< "char* " << std::endl;
	std::for_each(args.begin(),args.end(),[](char* s)
			{
			std::cout << s << std::endl;
			});
}






/*
struct CMD
{

	std::vector<std::string> args;
	std::string outfile;
	std::string infile;

};

// first we break the string down into CMDs


std::vector<CMD> parse(std::string);
void exec(CMD);

// maybe exec is a function call and its contents are listed below

auto cmd = parse(line);
int p[2][2];
int cur_in = 0;
int cur_out = 1;

for(auto&& c:cmd)
(
	pipe(p[cur_out]);
	auto pid=fork();
	if(pid<0)
	(
		//error
	)
	if(pid == 0)
	(
		dup2(p[cur_in][0],STD_IN);
	)
	if(pid > 0)
	(
		int status;
		waitpid(pid,&status,0);
		std::swap(cur_in,cur_out);
	)

)


*/


/*
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class or by finding sources on the internet
ie... (https://brennan.io/2015/01/16/write-a-shell-in-c/). But it has 
been altered and appended to by me Brigham Michaelis
*/
int main()
{
	double elapsed_child_time = 0;
	while(1)
	{
		std::string userInput;

		std::cout << "[cmd]:";
		getline(std::cin,userInput);

		std::vector<std::string> words = stringToVector(userInput);
		//printStringVector(words);

		std::vector<char*> args = sVectToCVect(words);
		//printCharVector(args);

		if(words[0] == "ptime")
		{
			std::cout<< "Time spent executing child processes:  "  << elapsed_child_time << " seconds." <<std::endl;
			continue;
		}


		if(words[0] == "exit")
		{
			std::cout<< "trying to exit" << std::endl;
			return (EXIT_SUCCESS);
		}
		auto start = std::chrono::steady_clock::now();
		auto pid = fork();
		if(pid < 0)
		{
			perror("error handling");
			exit(EXIT_FAILURE);
		}

		if(pid == 0)
		{
			if(execvp(args[0],args.data()) == -1)
			{
				perror("invalid");
			}
			exit(EXIT_FAILURE);
			//execvp(args[0],args.data());
		}

		else
		{
			int status;
			waitpid(pid,&status,0);
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			elapsed_child_time = elapsed_child_time + elapsed_seconds.count();
		}	
	}



	return 0;
}

