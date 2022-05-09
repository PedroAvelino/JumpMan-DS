#pragma once


template<typename T>
class Singleton
{
public:


	//Create a new instance of the singleton class
	static void CreateInstance();

	//Function that returns a the instance of the singleton
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

	//Destroys the instance of the singleton and sets it to null
	static void DestroyInstance();


protected:
	//Make the constructor and destructor protected to block new instances
	Singleton() {};
	~Singleton() {};

	//Disable copy contructor
	Singleton(const Singleton& other) = delete;

	//Disable copy assignment operator
	Singleton& operator=(const Singleton& other) = delete;

// private:
// 	inline static T* mInstance = nullptr;
};

// template<typename T>
// void Singleton<T>::CreateInstance()
// {
// 	//If there's no current instance, create a new one
// 	if (mInstance == nullptr)
// 	{
// 		mInstance = new T();
// 	}
// }

// template<typename T>
// T* Singleton<T>::GetInstance()
// {
// 	if (mInstance == nullptr)
// 	{
// 		CreateInstance();
// 	}
// 	//Return the instance
// 	return mInstance;
// }


// template<typename T>
// void Singleton<T>::DestroyInstance() {
// 	//delete the current instance
// 	delete mInstance;

// 	//Set it to null so we don't have a dangling pointer
// 	mInstance = nullptr;
// }


