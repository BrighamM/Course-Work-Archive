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
Some of the code in the following section was 
copied or obtained from class by Dr. Sundberg, 
or by Justin Bradshaw who is one of the CSS 
tutors and a student in the class. But it has 
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
			exit(1);
		}

		if(pid == 0)
		{
			execvp(args[0],args.data());
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


/*
	 int main()
	 {

	 std::string line;
	 std::getline(std::cin,line);
	 std::vector<std::string> words;
	 auto curr = line.begin();
	 while(std::distance(curr,line.end()) >= 0)
	 {
	 auto next = std::find(curr,line.end(),' ');
	 words.emplace_back(curr,next);
	 curr = next;
	 ++curr;
	 }

	 for(int w = 0;w<((int)words.size());w++)
	 {
	 std::cout << words[w] << " " << std::endl;
	 }

//std::vector<char*> args;
//std::transform(words.begin(),words.end(),std::back_inserter(args),
//[](auto w){return w.data();});
//args.push_back(nullptr);

execlp("ls","ls","-1",nullptr);
//execvp(args[0],args.data());



return 0;
}
 */
