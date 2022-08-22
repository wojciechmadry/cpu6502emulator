#include "instruction.hpp"
#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "utility/test_utils.hpp"

#include <exception>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool LABEL_AND_COMMENT_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    cpu6502::interpreter::Interpreter interp(cpu);
    auto& PC = cpu.get_registers().PC;

    // Test comment
    auto testComment = [&](const std::string& comment, bool isGood)
    {
        try
        {
            auto result = interp.interprete(comment);
            if (isGood)
            {
                all_good &= result == cpu6502::interpreter::Addressing::Comment;
            }
            else
            {
                all_good &= result != cpu6502::interpreter::Addressing::Comment;
            }
        }
        catch(const std::exception&) 
        {
            if (isGood)
            {
                all_good = false;
            }
        }
    };
    const std::string goodComment1 = "#Comment1";
    const std::string goodComment2 = "#Agh";
    const std::string goodComment3 = " ";
    const std::string goodComment4 = "";
    const std::string badComment1 = " #SomeComment";
    const std::string badComment2 = "!#SomeComment";

    testComment(goodComment1, true);
    testComment(goodComment2, true);
    testComment(goodComment3, true);
    testComment(goodComment4, true);
    testComment(badComment1, false);
    testComment(badComment2, false);

    // Test create label
    auto testCreateLabel = [&](const std::string& command, bool isGood, const std::string& labelName = "", std::uint32_t value = 0)
    {
        try 
        {
            auto result = interp.interprete(command);
            if (isGood)
            {
                const auto& labels = interp.get_labels();
                const auto found = labels.find(labelName);
                if (found != labels.end())
                {
                    all_good &= found->second == value;
                }
                else
                {
                    all_good = false;
                }
            }
            else
            {
                all_good = false;
            }
        } 
        catch (const std::exception&) 
        {
            if (isGood)
            {
                all_good = false;
            }
        }
    };

    const std::string goodLabel1 = "lab1:=15";
    testCreateLabel(goodLabel1, true, "LAB1", 15);

    const std::string goodLabel2 = "LaB2:=300";
    testCreateLabel(goodLabel2, true, "LAB2", 300);

    const std::string goodLabel3 = "LAB3:=0x16";
    testCreateLabel(goodLabel3, true, "LAB3", 0x16);

    const std::string goodLabel4 = "LAB4:=0xAf";
    testCreateLabel(goodLabel4, true, "LAB4", 0xaf);

    const std::string goodLabel5 = "LAb5:=ab";
    testCreateLabel(goodLabel5, true, "LAB5", 0xab);

    const std::string goodLabel6 = "Lab6:";
    testCreateLabel(goodLabel6, true, "LAB6", PC.get());

    utils::jump_to_2020(cpu);
    const std::string goodLabel7 = "LaB7:";
    testCreateLabel(goodLabel7, true, "LAB7", 0x2020);
    
    const std::string badLabel1 = "xx:==12";
    const std::string badLabel2 = "xx:=!12";
    const std::string badLabel3 = "abc:=??";
    const std::string badLabel4 = "abc:=j";
    const std::string badLabel5 = "abc:j";
    const std::string badLabel6 = "abc::";
    const std::string badLabel7 = ":";
    const std::string badLabel8 = ":=";


    testCreateLabel(badLabel1, false);
    testCreateLabel(badLabel2, false);
    testCreateLabel(badLabel3, false);
    testCreateLabel(badLabel4, false);
    testCreateLabel(badLabel5, false);
    testCreateLabel(badLabel6, false);
    testCreateLabel(badLabel7, false);
    testCreateLabel(badLabel8, false);

    return all_good;
}

}
