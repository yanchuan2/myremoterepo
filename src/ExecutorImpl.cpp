#include "ExecutorImpl.hpp"
#include <memory>
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
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

        if(cmder)
        {
            cmder->DoOperate(*this);//最外层的函数是ExecutorImpl类型的指针调用的，所以*this是executor
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
 Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
// namespace adas
