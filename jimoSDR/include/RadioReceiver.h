/// @file radio_receiver.h
/// @copyright Copyright © 2022 Jim Orcheson. Licensed under GPL version 3.0

#pragma once
//#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "ReceiverTask.h"
#include "ReceiverAction.h"

namespace jimo_sdr
{
    class RadioReceiver
    {
        public:
            ~RadioReceiver() noexcept;
            static RadioReceiver& GetInstance();
            void QueueTask(const ReceiverAction& action);
            void Process();
        private:
            RadioReceiver();
            static RadioReceiver* m_receiver;
            std::unique_ptr<std::thread> m_thread;
            std::atomic<bool> m_runReceive;
            std::queue<ReceiverAction> m_queue;
            std::mutex m_queueMutex;
            std::condition_variable m_entryInQueue;
    };
}