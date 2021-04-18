#include <iostream>
#include <string>
#include <vector>


#include "timer.h"
#include "ctpl_stl.h"



void add(int id, int count);
void addFloat(int id, int count);
void runThreadTest(int numTasks, int numThreads);

std::mutex cout_mutex;

int main()
{
	int numTasks = 16;
	int numThreads = 4;

	if (numThreads > 4)
	{
		std::cout << "Too many threads!\n";
		return 0;
	}
		

	Timer timer("no_hyperthreading_test6.csv");

	timer.WriteHeader();

	

	for (int th = 1; th <= numThreads; th*=2)
	{
		timer.setnumThreads(th);
	//int th = 1;
		for (int task = 2; task <= numTasks ;task++)
		{
			timer.setNumTasks(task);
			timer.Start();
			runThreadTest(task, th);

			timer.Stop();
			timer.Calc();
			timer.WriteCSV();
			std::cout << "\n";
			std::cout <<th<<" threads, "<<task<<" tasks: "<< timer.GetDuration() << " seconds" << std::endl;
			std::cout << "\n";
		}
	}
}

void runThreadTest(int numTasks, int numThreads)
{
	ctpl::thread_pool pool(numThreads);

	for (int i = 0; i < numTasks; i++)
	{
		pool.push(add, i+1);
		//std::cout<<"id "<<pool.get_thread(0).get_id()<<std::endl;
	}
}

void add(int id, int count)
{
	std::unique_lock<std::mutex> cout_lock(cout_mutex);

	std::cout << "started task " << count << std::endl;
	cout_lock.unlock();

	int sum = 0;
	//float sumf = 0.0f;
	for (int i = 0; i < 600000000; i++)
	{
		sum++;
		//sumf += 1.01f;
	}	

	cout_lock.lock();
	std::cout << "Finished task " << count << ", int sum is " << sum << std::endl;
	//std::cout << "Finished task " << count << ", int sum is " << sum <<"float sum is "<<sumf<< std::endl;
	cout_lock.unlock();
}

void addFloat(int id, int count)
{
	std::unique_lock<std::mutex> cout_lock(cout_mutex);

	std::cout << "started task " << count << std::endl;
	cout_lock.unlock();

	float sum = 0.0f;
	for (float i = 0; i < 300000000; i++)
	{
		sum+=1.0f;
	}

	cout_lock.lock();
	std::cout << "Finished task " << count << ", sum is " << sum << std::endl<<std::endl;
	cout_lock.unlock();
}


