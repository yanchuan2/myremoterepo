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
        // 前进功能
        if (commands[i] == 'M') {
            std::unique_ptr<Movecommand> cmder = std::make_unique<Movecommand>();
            cmder->DoOperate(*this);
        }
        else if(commands[i]=='L')
        {
            std::unique_ptr<TurnLeftcommand> cmder = std::make_unique<TurnLeftcommand>();
            cmder->DoOperate(*this);
        }
        else if(commands[i]=='R')
        {
            std::unique_ptr<TurnRightcommand> cmder = std::make_unique<TurnRightcommand>();
            cmder->DoOperate(*this);
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
