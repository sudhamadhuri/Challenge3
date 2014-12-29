// bufferCircular.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/circular_buffer.hpp>


#include "Circbuffer.h"
#include "Consumer.h"

template<class Buffer>
void fifo_test(Buffer* buffer) {
	
  
    boost::progress_timer progress;

    // Initialize the buffer with some values before launching producer and consumer threads.
    for (unsigned long i = QUEUE_SIZE / 2L; i > 0; --i) {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
        buffer->push_front(Buffer::value_type());
#else
         buffer->push_front(BOOST_DEDUCED_TYPENAME Buffer::value_type());
#endif
    }

    Consumer<Buffer> consumer(buffer);
    Producer<Buffer> producer(buffer);

    // Start the threads.
	
    boost::thread consume(consumer);
    boost::thread produce(producer);

    
	
}



int main(int argc, char** argv)
{
    bounded_buffer<int> bb_int(QUEUE_SIZE);
    std::cout << "bounded_buffer<int> ";
	while(1)
	{
    fifo_test(&bb_int);
	}

    return 0;
}