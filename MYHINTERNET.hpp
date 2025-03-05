/**
 * @brief This is a RAII wrapper for HINTERNET
 */

struct MYHINTERNET
{
    HINTERNET m_handle{ nullptr };

    MYHINTERNET() noexcept = default;
    explicit MYHINTERNET(HINTERNET h) noexcept : m_handle(h) {}

    /* Move constructor and move assignment operator can be optional in a 
     * minimal implementation if you know what you are doing
    */

    // Move constructor transfers ownership.
    MYHINTERNET(MYHINTERNET&& other) noexcept : m_handle(other.m_handle) {
        other.m_handle = nullptr;
    }

    // Move assignment operator transfers ownership.
    MYHINTERNET& operator=(MYHINTERNET&& other) noexcept {
        if (this != &other) {
            if (m_handle) {
                InternetCloseHandle(m_handle);
            }
            m_handle = other.m_handle;
            other.m_handle = nullptr;
        }
        return *this;
    }

    // Assignment operator for HINTERNET
    MYHINTERNET& operator=(HINTERNET h) noexcept {
        if (m_handle != h) {  // Guard against self-assignment
            InternetCloseHandle(m_handle);
            m_handle = h;
        }
        return *this;
    }

    // Deleted copy operations
    MYHINTERNET(const MYHINTERNET&) = delete;
    MYHINTERNET& operator=(const MYHINTERNET&) = delete;

    // Destructor releases the handle
    ~MYHINTERNET() { INET_CLOSE_HANDLE(m_handle); }

    // conversion operator to allow using the object where HINTERNET is required
    operator HINTERNET() const noexcept { return m_handle; }
};