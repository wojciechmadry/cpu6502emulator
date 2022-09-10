#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"

#include <array>
#include <algorithm>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool FACTORIAL_TEST()
{
    static constexpr std::size_t lastN = 5u;

    constexpr auto generate_array = []()
    {
        std::array<std::size_t, lastN + 1> result;
        for(std::size_t i = 0u ; i < result.size() ; ++i)
        {
            std::size_t n{1}, fact{1};
            do{
                fact *= n;
                ++n;
            } while(n <= i);
            result[i] = fact;
        }
        return result;
    };

    static constexpr auto factorialArray = generate_array(); 
    static_assert(factorialArray[0] == 1);
    static_assert(factorialArray[1] == 1);
    static_assert(factorialArray[2] == 2);
    static_assert(factorialArray[3] == 6);
    static_assert(factorialArray[4] == 24);
    static_assert(factorialArray[5] == 120);

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

    static constexpr auto asmFile = "examples/factorial.asm";

    for(std::size_t n = 0 ; n < factorialArray.size() ; ++n)
    {
        interp.load_asm(asmFile);
        all_good &= checkLabel("N", 1333u);
        all_good &= checkLabel("MAIN", 720);
        all_good &= checkLabel("I", 5040u);
        
        
        auto& commands = interp.get_commands();
        auto nSetCommand = std::find(commands.begin(), commands.end(), "LDA #5");
        if (nSetCommand == commands.end())
        {
            all_good &= false;
            break;
        }
        (*nSetCommand) = "LDA #" + std::to_string(n);
        interp.execute_asm();
        all_good &= cpu.get_registers().ACU.get() == factorialArray[n];
        
        interp.get_cpu().reset();
    }



    return all_good;
}

}
