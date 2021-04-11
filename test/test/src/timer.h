#pragma once

#include <chrono>
#include <fstream>

class Timer {

	int m_numThreads, m_numTasks;
	long double start, end, duration;


public:
	std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> m_endTimepoint;
	std::string m_inFile, m_outFile;



	// Default Constructor
	Timer()
		:m_outFile("hyperthreading.csv"), start(0), end(0), duration(0) {
		//WriteHeader();
	}

	// Constructor to specify outfile, numTasks, numThreads
	Timer(const std::string& outFile)
		: m_outFile(outFile), m_numTasks(1), m_numThreads(1), start(0), end(0), duration(0) {
		//WriteHeader();
	}

	// Constructor to specify outfile, numTasks, numThreads
	Timer(const std::string& outFile, int numTasks)
		: m_outFile(outFile), m_numTasks(numTasks), m_numThreads(1), start(0), end(0), duration(0) {
		//WriteHeader();
	}

	// Constructor to specify outfile, numTasks, numThreads
	Timer(const std::string& outFile, int numTasks, int numThreads)
		: m_outFile(outFile), m_numTasks(numTasks), m_numThreads(numThreads), start(0), end(0), duration(0) {
		//WriteHeader();
	}

	void Calc() {
		start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_startTimePoint).time_since_epoch().count();
		end = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_endTimepoint).time_since_epoch().count();
		duration = (end - start) * 0.000001;
		duration /= 1000.0f;
	}

	void Reset() {
		start = end = duration = 0;
	}

	void WriteHeader() {
		std::ofstream oStream;
		oStream.open(m_outFile, std::ios::app);
		oStream << "num_threads,num_tasks,duration(s)" << std::endl;
		oStream.close();
	}


	void WriteCSV() {
		std::ofstream oStream;
		oStream.open(m_outFile, std::ios::app);
		oStream << m_numThreads << "," << m_numTasks << "," << duration << std::endl;
		oStream.close();
	}


	inline void Start() { m_startTimePoint = std::chrono::steady_clock::now(); }
	inline void Stop() { m_endTimepoint = std::chrono::steady_clock::now(); }
	inline void setnumThreads(int num) { this->m_numThreads = num; }
	inline void setNumTasks(int num) { this->m_numTasks = num; }

	inline long double GetDuration() { return this->duration; }
};