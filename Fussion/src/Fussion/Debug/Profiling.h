#pragma once
#include <chrono>
#include <fstream>

namespace Fussion
{
    struct ProfileResult {
        const char *Name;
        std::chrono::system_clock::time_point TimeStamp;
    };

    class TimeStamp;
    class Profiler
    {
        static Profiler s_instance;
        std::ofstream m_file{};
        std::chrono::system_clock::time_point m_profileStartTime{};
        bool m_enabled{false};

    public:
        void BeginProfile(const String &fileName)
        {
            m_enabled = true;
            m_profileStartTime = std::chrono::high_resolution_clock::now();
            // m_profileStartTime =
            // std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
            if (m_file.is_open())
                m_file.close();

            m_file.open(fileName, std::ios::out);
            m_file << "[\n";
        }

        void Begin(const ProfileResult &result)
        {
            if (!m_enabled || !m_file.is_open())
                return;
            auto diff =
                std::chrono::duration_cast<std::chrono::microseconds>(result.TimeStamp - m_profileStartTime).count();
            m_file << "\t{\n";
            m_file << "\t\t\"name\": \"" << result.Name << "\",\n";
            m_file << "\t\t\"cat\": \"PERF\",\n";
            m_file << "\t\t\"ph\": \"B\",\n";
            m_file << "\t\t\"pid\": 0,\n";
            m_file << "\t\t\"tid\": 0,\n";
            m_file << "\t\t\"ts\": " << std::to_string(diff) << "\n";
            m_file << "\t},\n";
            m_file.flush();
        }

        void End(const ProfileResult &result)
        {
            if (!m_enabled || !m_file.is_open())
                return;
            auto diff =
                std::chrono::duration_cast<std::chrono::microseconds>(result.TimeStamp - m_profileStartTime).count();
            m_file << "\t{\n";
            m_file << "\t\t\"name\": \"" << result.Name << "\",\n";
            m_file << "\t\t\"cat\": \"PERF\",\n";
            m_file << "\t\t\"ph\": \"E\",\n";
            m_file << "\t\t\"pid\": 0,\n";
            m_file << "\t\t\"tid\": 0,\n";
            m_file << "\t\t\"ts\": " << std::to_string(diff) << "\n";
            m_file << "\t},\n";
            m_file.flush();
        }

        void EndProfile()
        {
            m_enabled = false;
            m_file << "]\n";
            m_file.flush();
            m_file.close();
        }

        void SetEnabled(bool value)
        {
            m_enabled = value;
        }

        bool IsEnabled()
        {
            return m_enabled;
        }

        static Profiler &Get()
        {
            return s_instance;
        }
    };

    class TimeStamp
    {
        const char *m_name{};
        std::chrono::system_clock::time_point m_start;

    public:
        TimeStamp(const char *name) : m_name(name)
        {
            m_start = std::chrono::high_resolution_clock::now();
            Profiler::Get().Begin({m_name, m_start});
        }

        ~TimeStamp()
        {
            auto end = std::chrono::high_resolution_clock::now();
            Profiler::Get().End({m_name, end});
        }
    };
} // namespace Fussion

#ifdef FSN_ENABLE_PROFILING
    #define FSN_TOKEN_PASTE(x, y) x##y
    #define FSN_TOKEN_CAT(x, y) FSN_TOKEN_PASTE(x, y)
    #define FSN_BEGIN_PROFILE(name) ::Fussion::Profiler::Get().BeginProfile(name)
    #define FSN_END_PROFILE(name) ::Fussion::Profiler::Get().EndProfile(name)
    #define FSN_PROFILE_SCOPE(ScopeName) ::Fussion::TimeStamp FSN_TOKEN_CAT(timeStamp, __LINE__)(ScopeName)
    #define FSN_PROFILE_FUNCTION() FSN_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define FSN_BEGIN_PROFILE(name)
    #define FSN_END_PROFILE(name)
    #define FSN_PROFILE_SCOPE(ScopeName)
    #define FSN_PROFILE_FUNCTION
#endif
