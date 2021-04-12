#include <iostream>
#include <string>
#include <vector>


#include "timer.h"
#include "ctpl_stl.h"


void add(int id, int count);
void runThreadTest(int numTasks, int numThreads);

std::mutex cout_mutex;

int main()
{
	int numTasks = 16;
	int numThreads = 4;
	Timer timer("no_hyperthreading_test3.csv");

	timer.WriteHeader();

	for (int th = 1; th <= numThreads; th*=2)
	{
		timer.setnumThreads(th);
		for (int task = 1; task <= numTasks ;task++)
		{
			timer.setNumTasks(task);
			timer.Start();
			runThreadTest(task, th);

			timer.Stop();
			timer.Calc();
			timer.WriteCSV();
			std::cout <<th<<" threads, "<<task<<" tasks: "<< timer.GetDuration() << " seconds" << std::endl;
			std::cout << "\n";
		}
	}







	/*int numTasks = 4;
	int numThreads = 4;

	Timer timer;

	timer.Start();
	add(1,1); 
	timer.Stop();
	timer.Calc();

	std::cout << timer.GetDuration() << " seconds" << std::endl;

	timer.Start();
	runThreadTest(1, 1);
	timer.Stop();
	timer.Calc();
	std::cout << timer.GetDuration() << " seconds" << std::endl;


	timer.Start();

	runThreadTest(numTasks, 1);

	timer.Stop();
	timer.Calc();
	
	std::cout << timer.GetDuration() << " seconds" << std::endl;

	timer.Start();

	runThreadTest(numTasks, numTasks);

	timer.Stop();
	timer.Calc();
	std::cout << timer.GetDuration() <<" seconds"<< std::endl;*/
}

void runThreadTest(int numTasks, int numThreads)
{
	ctpl::thread_pool pool(numThreads);

	for (int i = 0; i < numTasks; i++)
	{
		pool.push(add, i+1);
	}
}

void add(int id, int count)
{
	std::unique_lock<std::mutex> cout_lock(cout_mutex);

	std::cout << "started task " << count << std::endl;
	cout_lock.unlock();

	int sum = 0;
	for (int i = 0; i < 600000000; i++)
	{
		sum++;
	}

	cout_lock.lock();
	std::cout << "Finished task " << count << ", sum is " << sum << std::endl;
	cout_lock.unlock();
}


