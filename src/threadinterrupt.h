// Copyright (c) 2016 The URALS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef URALS_THREADINTERRUPT_H
#define URALS_THREADINTERRUPT_H

#include <atomic>
//#include <chrono>
//#include <condition_variable>
//#include <mutex>
#include <boost/thread.hpp>

/*
    A helper class for interruptible sleeps. Calling operator() will interrupt
    any current sleep, and after that point operator bool() will return true
    until reset.
*/
class CThreadInterrupt
{
public:
    explicit operator bool() const;
    void operator()();
    void reset();
    bool sleep_for(boost::chrono::milliseconds rel_time);
    bool sleep_for(boost::chrono::seconds rel_time);
    bool sleep_for(boost::chrono::minutes rel_time);

private:
    boost::condition_variable cond;
    boost::mutex mut;
    std::atomic<bool> flag;
};

#endif //URALS_THREADINTERRUPT_H
