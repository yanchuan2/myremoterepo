#include "ExecutorImpl.hpp"
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
            Move();
        }
    }
    return;
}
void ExecutorImpl::Move() noexcept
{
    if(pose.heading=='E'){
        ++pose.x;
    }else if(pose.heading=='W'){
        --pose.x;
    }else if(pose.heading=='N'){
        ++pose.y;
    }else if(pose.heading=='S'){
        --pose.y;
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
// namespace adas
