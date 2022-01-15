#ifndef WORKERACTION_H
#define WORKERACTION_H

#include<iostream>
#include<functional>

typedef std::function<void()> Action;

class WorkerAction
{
    public:
        WorkerAction(Action actionFn);
        virtual ~WorkerAction();

        void SetAction(Action actionFn) { MyAction = actionFn; }

        void Execute();

    private:

        Action MyAction = nullptr;
};
#endif // WORKERACTION_H
