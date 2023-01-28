#pragma once
#include <chrono>
#include <fstream>

namespace Fussion
{
    struct ProfileResult {
        const char *Name{};
        std::chrono::high_resolution_clock::time_point TimeStamp{};
    };

    class TimeStamp;
    class Profiler
    {
        static Profiler s_instance;
        std::ofstream m_file{};
        std::chrono::high_resolution_clock::time_point m_profileStartTime{};
        bool m_enabled{false};

    public:
        void begin_profile(const String &fileName)
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

        void begin(const ProfileResult &result)
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

        void end(const ProfileResult &result)
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

        void end_profile()
        {
            m_enabled = false;
            m_file << "]\n";
            m_file.flush();
            m_file.close();
        }

        void set_enabled(bool value)
        {
            m_enabled = value;
        }

        bool is_enabled() const
        {
            return m_enabled;
        }

        static Profiler &get()
        {
            return s_instance;
        }
    };

    class TimeStamp
    {
        const char *m_name{};
        std::chrono::high_resolution_clock::time_point m_start;

    public:
        explicit TimeStamp(const char *name) : m_name(name)
        {
            m_start = std::chrono::high_resolution_clock::now();
            Profiler::get().begin(ProfileResult{m_name, m_start});
        }

        ~TimeStamp()
        {
            auto end = std::chrono::high_resolution_clock::now();
            Profiler::get().end(ProfileResult{m_name, end});
        }
    };
} // namespace Fussion

#if defined(_MSC_VER)
    #define BUILTIN_FUNC_SIG __FUNCSIG__
#elif defined(__clang__) || defined(__GNUC__)
    #define BUILTIN_FUNC_SIG __PRETTY_FUNCTION__
#endif

#ifdef FSN_ENABLE_PROFILING
    #define FSN_TOKEN_PASTE(x, y) x##y
    #define FSN_TOKEN_CAT(x, y) FSN_TOKEN_PASTE(x, y)
    #define FSN_BEGIN_PROFILE(name) ::Fussion::Profiler::get().begin_profile(name)
    #define FSN_END_PROFILE(name) ::Fussion::Profiler::get().end_profile(name)
    #define FSN_PROFILE_SCOPE(ScopeName) ::Fussion::TimeStamp FSN_TOKEN_CAT(timeStamp, __LINE__)(ScopeName)
    #define FSN_PROFILE_FUNCTION() FSN_PROFILE_SCOPE(BUILTIN_FUNC_SIG)
#else
    #define FSN_BEGIN_PROFILE(name)
    #define FSN_END_PROFILE(name)
    #define FSN_PROFILE_SCOPE(ScopeName)
    #define FSN_PROFILE_FUNCTION()
#endif
