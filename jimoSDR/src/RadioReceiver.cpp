#include "RadioReceiver.h"
#include "Devices.h"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

namespace jimo_sdr
{
    RadioReceiver::~RadioReceiver() noexcept
    {
        m_thread->join();
        if (m_receiver != nullptr)
        {
            delete m_receiver;
        }
    }

    RadioReceiver::RadioReceiver()
    {
        m_thread = std::make_unique<std::thread>([this]() { Process(); });
    }

    RadioReceiver& RadioReceiver::GetInstance()
    {
        if (!m_receiver)
        {
            m_receiver = new RadioReceiver;
        }
        return *m_receiver;
    }

    void RadioReceiver::QueueTask(const ReceiverAction& action)
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_queue.push(action);
        m_entryInQueue.notify_all();
    }

    void RadioReceiver::Process()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            lock.unlock();
            while (!m_runReceive && m_queue.empty())
            {
                lock.lock();
                m_entryInQueue.wait(lock);
                lock.unlock();
                break;
            }
            while (true)
            {
                lock.lock();
                if (m_queue.empty())
                {
                    lock.unlock();
                    break;
                }
                else
                {
                    ReceiverAction action = m_queue.front();
                    m_queue.pop();
                    lock.unlock();
                    std::shared_ptr<sdr::Device> device;
                    switch (action.task)
                    {
                        case ReceiverTask::getReceivers:
                            std::invoke(action.callback, sdr::devices());
                            break;
                        case ReceiverTask::getDriverKey:
                            {
                                device = any_cast<std::shared_ptr<sdr::Device>>(action.m_data);
                                std::string key = device->GetDriverKey();
                                std::invoke(action.callback, key);
                            }
                            break;
                        case ReceiverTask::getSampleRates:
                            {
                                device = any_cast<std::shared_ptr<sdr::Device>>(action.m_data);
                                std::vector<double> rates = device->sample_rates(
                                    sdr::Device::direction::rx, 0);
                                std::invoke(action.callback, rates);
                            }
                            break;
                        case ReceiverTask::getCurrentSampleRate:
                            {
                                device = any_cast<std::shared_ptr<sdr::Device>>(action.m_data);
                                double rate = device->sample_rate(
                                    sdr::Device::direction::rx, 0);
                                std::invoke(action.callback, rate);
                            }
                            break;
                    }
                }
            }
            if (m_runReceive)
            {
                // simulate receiving data for now
                std::this_thread::sleep_for(30ms);
                std::cout << "Running";
            }
        }
    }

    RadioReceiver* RadioReceiver::m_receiver = nullptr;
}