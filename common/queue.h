#ifndef QUEUE_H_
#define QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC)
 *
 * Queue is a generic MPMC queue with blocking operations
 * push() and pop().
 *
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 * On a closed queue, any method will raise ClosedQueue.
 *
 * */
template <typename T, class C = std::deque<T> >
class Queue {
private:
    std::queue<T, C> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;


    // Popea un batch de todos los elementos disponibles, a lo sumo count. Y lo guarda en el vector.
    std::vector<T> try_pop_batch(int count) {
        std::unique_lock<std::mutex> lck(mtx);
        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return std::vector<T>();  // Sin elementos.
        }

        std::vector<T> res;

        res.reserve(count);

        while (count > 0) {
            res.push_back(q.front());
            q.pop();
            count--;
        }


        return res;
    }

public:
    // Permiti empezarla inicialmente cerrada y que se reabra despues.
    // explicit Queue(const bool _closed): max_size(UINT_MAX - 1), closed(_closed) {}
    explicit Queue(const unsigned int max_size, const bool _closed):
            max_size(max_size), closed(_closed) {}

    Queue(): Queue(false) {}
    explicit Queue(const unsigned int max_size): Queue(max_size, false) {}


    bool try_push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    // Dos opciones para el pop batch a vector.
    std::vector<T> pop_batch(int count) {
        return try_pop_batch(q.size() < count ? q.size() : count);
    }

    std::vector<T> pop_batch() { return try_pop_batch(q.size()); }

    // Popea todos los elementos, a lo sumo la cantidad count.
    int pop_batch(T* init, unsigned int count) {
        std::unique_lock<std::mutex> lck(mtx);
        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return 0;  // Sin elementos.
        }
        if (q.size() < count) {
            count = q.size();
        }

        unsigned int ind = 0;
        while (ind < count) {
            *(init + ind) = q.front();
            q.pop();
            ind += 1;
        }
        return ind;
    }

    bool try_pop(T& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    void push(T const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
    }


    T pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        T const val = q.front();
        q.pop();

        return val;
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

    bool isclosed() {
        std::unique_lock<std::mutex> lck(mtx);
        return closed;
    }

    bool reopen() {
        std::unique_lock<std::mutex> lck(mtx);
        if (closed) {
            // Aseguremosnos esta vacia la queue.
            std::queue<T, C> new_q;
            std::swap(q, new_q);
            closed = false;
            return true;
        }

        return false;
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};
#endif
