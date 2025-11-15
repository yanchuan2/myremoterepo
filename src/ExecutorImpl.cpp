#include "ExecutorImpl.hpp"

#include <memory>
#include <unordered_map>

#include "CmderFactory.hpp"
#include "Command.hpp"
#include "Singleton.hpp"
#include <algorithm>
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
    //std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap;
    //cmderMap.emplace('M', MoveCommand());
    //cmderMap.emplace('L', TurnLeftCommand());
    //cmderMap.emplace('R', TurnRightCommand());
    //cmderMap.emplace('F', FastCommand());
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

    std::for_each
    (
        cmders.begin(), cmders.end(),
        [this](const Cmder& cmder) noexcept { cmder(poseHandler); }
    );
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
    fast = !fast;
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
