#include<cstddef>
#include<memory>

class Arena {
public:
    explicit Arena(std::size_t capacity);

    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;

    std::byte* allocate(std::size_t size);
    void reset() noexcept{used_ = 0;}
    [[nodiscard]] std::size_t capacity()  const noexcept
    {
	    return capacity_;
    }
    [[nodiscard]] std::size_t used() const noexcept
    {
	    return used_;
    }

private:
    std::unique_ptr<std::byte[]> storage_;
    std::size_t capacity_;
    std::size_t used_ = 0;
};
