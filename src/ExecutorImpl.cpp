#include "ExecutorImpl.hpp"
#include <memory>
#include "Command.hpp"
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (int i = 0; i < (int)commands.size(); i++) {
        std::unique_ptr<ICommand> cmder;

        if(commands[i]=='M')
        {
            cmder=std::make_unique<MoveCommand>();
        }
        else if(commands[i]=='L')
        {
            cmder=std::make_unique<TurnLeftCommand>();
        }
        else if(commands[i]=='R')
        {
            cmder=std::make_unique<TurnRightCommand>();
        }
        else if(commands[i]=='F')
        {
            cmder = std::make_unique<FastCommand>();
        }


        if(cmder)
        {
            cmder->DoOperate(poseHandler);//最外层的函数是ExecutorImpl类型的指针调用的，所以*this是executor
        }
    }
    return;
}
void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 'E') {
        ++pose.x;
    } else if (pose.heading == 'W') {
        --pose.x;
    } else if (pose.heading == 'N') {
        ++pose.y;
    } else if (pose.heading == 'S') {
        --pose.y;
    }
}
void ExecutorImpl::TurnLeft() noexcept
{
        if (pose.heading == 'N') {
            pose.heading = 'W';
        } else if (pose.heading == 'E') {
            pose.heading = 'N';
        } else if (pose.heading == 'S') {
            pose.heading = 'E';
        } else if (pose.heading == 'W') {
            pose.heading = 'S';
        }
}
void ExecutorImpl::TurnRight() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'E';
    } else if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    }
}
void ExecutorImpl::Fast() noexcept
{
    fast=!fast;
}
bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}
Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
// namespace adas
