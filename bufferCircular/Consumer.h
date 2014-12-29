
#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/call_traits.hpp>
#include <boost/progress.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include <deque>

const unsigned long QUEUE_SIZE     = 1000L;
const unsigned long TOTAL_ELEMENTS = QUEUE_SIZE * 1000L;

template<class Buffer>
class Consumer {

    typedef typename Buffer::value_type value_type;
    Buffer* m_container;
    value_type m_item;
	
public:
    Consumer(Buffer* buffer) : m_container(buffer) {}

    void operator()() {
		 std::fstream myfile;
		myfile.open ("myfile.h5");
		while(1)
		{
        for (unsigned long i = 0L; i < TOTAL_ELEMENTS; ++i) {
            m_container->pop_back(&m_item);
			 myfile <<m_item;
        }

		}
    }
};

template<class Buffer>
class Producer {

    typedef typename Buffer::value_type value_type;
    Buffer* m_container;

public:
    Producer(Buffer* buffer) : m_container(buffer) {}

    void operator()() {

		while(1)
		{
        for (unsigned long i = 0L; i < TOTAL_ELEMENTS; ++i) {
            m_container->push_front(value_type());
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
        }
    }
};