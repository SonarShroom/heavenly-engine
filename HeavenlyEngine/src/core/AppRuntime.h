#pragma once

namespace Heavenly {
struct AppRuntime {
    using RunFunc = void(*)();

    RunFunc runFunction = nullptr;
};
}
