#include "WorkerAction.h"

WorkerAction::WorkerAction(Action actionFn)
    : MyAction(actionFn)
{
    std::cout << "WorkerAction CTOR...\n";
}

WorkerAction::~WorkerAction()
{
    std::cout << "WorkerAction CTOR...\n";
    MyAction = nullptr;
}

void WorkerAction::Execute()
{
    if(MyAction)
    {
        std::cout << "WorkerAction::Executing...\n";
        MyAction();
        std::cout << "WorkerAction::Executed...\n";
    }
    else
    {
        std::cout << "WorkerAction::Action is NULL!!!\n";
    }
}
