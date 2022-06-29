// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#ifndef _SINGLETON_
#define _SINGLETON_
#include <memory>
#include <cassert>
#include <iostream>

/*
 * This is an attempt to have a single Singleton class that can be used via inheritance to make some other class Singleton.
 * It is just to avoid copying the Singleton declarations each time.
 *
 * >>>>> Usage:
 *
 * class A : public Singleton<A> {
 *    friend Singleton<A>; // this way Singleton can call the constructor of A
 * private: // constructors are private
 *    A() {
 *      //....
 *    }
 * public: // the rest of the functionality
 *    virtual ~A() {
 *		//....
 *    }
 * }
 */

template<typename T>
class Singleton {
protected:
	Singleton() {
	}

public:
	// cannot copy objects of this type
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;

	virtual ~Singleton() {
	}

	// some singletons need to be initialised with some parameters,
	// we can call this method at the beginning of the program
	template<typename ...Targs>
	MOTOR_API inline static T* init(Targs &&...args) {
		assert(instance_.get() == nullptr);
		instance_.reset(new T(std::forward<Targs>(args)...));
		return instance_.get();
	}

	// in some cases, when singletons depend on each other, you have to close them in a specific order,
	// this is why we have this close method
	MOTOR_API inline static void close() {
		instance_.reset();
	}

	// get the singleton instance as a pointer
	MOTOR_API inline static T* instance() {
		assert(instance_.get() != nullptr); // we force initialisation at the beginning
		return instance_.get();
	}

private:
	MOTOR_API static std::unique_ptr<T> instance_;
};

#endif // !_SINGLETON_
