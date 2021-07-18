//
// Created by ChaosChen on 2021/7/18.
//

#ifndef MOCKER_THREAD_H
#define MOCKER_THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>

namespace mocker {

    class Thread {
    public:
        typedef std::shared_ptr<Thread> ptr;
        using task = std::function<void()>;

        Thread(Thread::task cb, const std::string& name = "");
        ~Thread();

        pid_t getId() const { return m_id; }
        const std::string& getName() const { return m_name; }

        void join();

        static Thread* getCurrent();
        static const std::string& getCurrentName();
        static void setCurrentName(const std::string& name);
    private:
        Thread(const Thread&) = delete;
        Thread(const Thread&&) = delete;
        Thread& operator=(const Thread&) = delete;

        static void* run(void* arg);
    private:
        pid_t m_id = -1;
        pthread_t m_thread = 0;
        Thread::task m_cb;
        std::string m_name;
    };
}

#endif //MOCKER_THREAD_H