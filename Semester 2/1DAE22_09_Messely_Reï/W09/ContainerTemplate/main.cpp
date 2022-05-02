#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include "Container.h"
// TODO: 1. Uncomment these include directives
#include "TestContainerTemplate.h"
#include "Fraction.h"
#include "vector2f.h"

void TestInitializerList();
void TestVector2fContainer();

void StartHeapControl();
void DumpMemoryLeaks();

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	{
		StartHeapControl();
		
		// Test the constructor with initializer list parameter
		TestInitializerList();

		// TODO: 2. Uncomment these 3 code lines to test a container of int type elements
		std::cout << "\n-->Start of Container<int> test <--\n";
		TestContainer<int>( );
		std::cout << "-->End of Container<int> test <--\n\n";

		// TODO: 3. Uncomment these 3 code lines to test a container of float type elements
		std::cout << "-->Start of Container<float> test <--\n";
		TestContainer<float>( );
		std::cout << "-->End of Container<float> test <--\n\n";

		// TODO: 4. Uncomment these 3 code lines to test a container of string type elements
		std::cout << "-->Start of Container<string> test <--\n";
		TestContainer<std::string>( );
		std::cout << "-->End of Container<string> test <--\n\n";

		// TODO: 5. Uncomment these 3 code lines to test a container of Fraction type elements
		std::cout << "-->Start of Container<Fraction> test <--\n";
		TestContainer<Fraction>( );
		std::cout << "-->End of Container<Fraction> test <--\n\n";

		// TODO: 6. Uncomment these 3 code lines to test a constainer of Vector2f types
		std::cout << "-->Start of Container<Vector2f> test <--\n";
		TestVector2fContainer();
		std::cout << "-->End of Container<Vector2f> test <--\n";
	}
	DumpMemoryLeaks();

	std::cout << "Push ENTER to continue";
	std::cin.get();
}

void TestInitializerList()
{
	// Test 1
	// Create a Container object using braced-init-list of elements
	// Print the elements
	Container<int> cont1{ 1,2,3,4,5 };
	for (int idx{}; idx < cont1.Size(); ++idx)
	{
		std::cout << cont1[idx] << " ";
	}
	std::cout << "\n";

	// Test 2
	// Assign an braced-init-list to the above Container object
	// Print the elements
	cont1 = { 20,30,40 };
	for (int idx{}; idx < cont1.Size(); ++idx)
	{
		std::cout << cont1[idx] << " ";
	}
	std::cout << "\n";

	// Test 3
	// Which Container constructor is called?
	Container<int> cont2(40);
	Container<int> cont3{ 40 };
}

void TestVector2fContainer()
{
	// TODO: 7. Create a Container 'velocities' of Vector2f elements 
	// using the constructor with std::initializer_list parameter
	Container<Vector2f> velocities{ Vector2f{0,-9.81},Vector2f{100,100} };

	// TODO: 8. Add some elements, enough to expand the container
	velocities.PushBack(Vector2f{ 0,300 });
	velocities.PushBack(Vector2f{ 0,500 });

	// TODO: 9. Print the elements using a for loop and the operator[] of the container
	for (int i{ 0 }; i < velocities.Size(); ++i)
	{
		std::cout << velocities[i] << '\n';
	}

	// TODO: 10. Add value 10 to x-part of all the elements using the operator[] of the container
	for (int i{ 0 }; i < velocities.Size(); ++i)
	{
		velocities[i].x += 10;
	}

	// TODO: 11. Add value 5 to y-part of all the elements using the operator[] of the container
	for (int i{ 0 }; i < velocities.Size(); ++i)
	{
		velocities[i].y += 5;
	}

	// TODO: 12. Print the elements using a for loop and the method Get of the container
	for (int i{ 0 }; i < velocities.Size(); ++i)
	{
		std::cout << velocities.Get(i) << '\n';
	}

}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}
