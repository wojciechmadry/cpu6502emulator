#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"

#include <array>
#include <algorithm>
#include <string>
#include <fmt/core.h>
namespace CPU6502_TEST::interpreter_test::inner{


bool FIBONACCI_TEST()
{
    static constexpr std::size_t lastN = 13u;

    constexpr auto generate_array = []()
    {
        std::array<std::size_t, lastN + 1u> result;
        for(std::size_t i = 0u ; i <= lastN ; ++i)
        {
            std::size_t f0 = 0;
            std::size_t f1 = 1;
            for(std::size_t n = 1 ; n <= i ; ++n)
            {
                auto f2 = f0 + f1;
                f0 = f1;
                f1 = f2;
            }
            result[i] = f0;
        }
        return result;
    };

    static constexpr auto fibArray = generate_array(); 
    (void) fibArray;

    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    cpu6502::interpreter::Interpreter interp(cpu);
    const auto& labels = interp.get_labels();

    auto checkLabel = [&](const std::string& labelName, std::uint16_t labelValue) -> bool
    {
        const auto labelFound = labels.find(labelName);
        if (labelFound == labels.end())
        {
            return false;
        }
        return labels.at(labelName) == labelValue;
    };

    static constexpr auto asmFile = "examples/fibonacci.asm";

    for(std::size_t n = 0 ; n < fibArray.size() ; ++n)
    {
        interp.load_asm(asmFile);
        all_good &= checkLabel("N", 1333u);
        all_good &= checkLabel("MAIN", 1597u);
        all_good &= checkLabel("F0", 377u);
        all_good &= checkLabel("F1", 610u);
        all_good &= checkLabel("I", 2584u);
        
        auto& commands = interp.get_commands();
        auto nSetCommand = std::find(commands.begin(), commands.end(), "LDA #13");
        if (nSetCommand == commands.end())
        {
            all_good &= false;
            break;
        }

        (*nSetCommand) = "LDA #" + std::to_string(n);

        interp.execute_asm();
        
        //all_good &= mem[labels.at("I")] == n;
        all_good &= mem[labels.at("F1")] == fibArray[n];
        fmt::print("{} == {}\n", (int)mem[labels.at("F1")] , fibArray[n] );
        interp.get_cpu().reset();
    }



    return all_good;
}

}
