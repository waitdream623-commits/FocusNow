#include "storage.h"
#include <fstream>

namespace storage {

void RecomputeLetterDerived(LetterData& d)
{
    d.errorCount = d.totalCount - d.correctCount;
    d.accuracy = (d.totalCount > 0) ? (double)d.correctCount / d.totalCount : 0.0;
    d.avgReactionTime = (d.totalCount > 0) ? d.totalTime / d.totalCount : 0.0;
}

void AddSession(UserData& user, const SessionData& s)
{
    user.sessions.push_back(s);
    for (int i = 0; i < 26; i++)
    {
        LetterData& d = user.letters[i];
        d.totalCount += s.letters[i].totalCount;
        d.correctCount += s.letters[i].correctCount;
        d.totalTime += s.letters[i].totalTime;
        RecomputeLetterDerived(d);
    }
    user.mouse.total += s.mouse.total;
    user.mouse.correct += s.mouse.correct;
    user.mouse.errors += s.mouse.errors;
}

bool Save(const UserData& user, const std::string& path)
{
    std::ofstream out(path);
    if (!out) return false;
    out << "FocusNowSaveV1\n";
    out << user.name << '\n';
    out << user.sessions.size() << '\n';
    for (const SessionData& s : user.sessions)
    {
        out << s.timestamp << ' ' << s.duration << ' ' << s.wpm << ' '
            << s.mouse.total << ' ' << s.mouse.correct << ' ' << s.mouse.errors << '\n';
        for (int i = 0; i < 26; i++)
        {
            out << s.letters[i].totalCount << ' '
                << s.letters[i].correctCount << ' '
                << s.letters[i].totalTime << '\n';
        }
    }
    return (bool)out;
}

bool Load(UserData& user, const std::string& path)
{
    std::ifstream in(path);
    if (!in) return false;
    std::string magic;
    if (!(in >> magic) || magic != "FocusNowSaveV1") return false;
    in.ignore();// 跳过换行，准备用 getline 读名字
    std::string name;
    if (!std::getline(in, name)) return false;

    user = UserData{};// 清空，重新读取
    user.name = name;

    size_t sessionCount = 0;
    if (!(in >> sessionCount)) return false;
    for (size_t k = 0; k < sessionCount; k++)
    {
        SessionData s;
        if (!(in >> s.timestamp >> s.duration >> s.wpm
                  >> s.mouse.total >> s.mouse.correct >> s.mouse.errors))
            return false;
        for (int i = 0; i < 26; i++)
        {
            if (!(in >> s.letters[i].totalCount
                      >> s.letters[i].correctCount
                      >> s.letters[i].totalTime))
                return false;
            RecomputeLetterDerived(s.letters[i]);
        }
        AddSession(user, s);
    }
    return true;
}

}
