
#include "encoder.hpp"

namespace kodo
{
    virtual uint32_t encoder::encode(uint8_t* payload)
    {
        return m_wrapper.encode(payload);
    }

    virtual void encoder::set_symbols(const uint8_t* data, uint32_t size)
    {
        m_wrapper(data, size);
    }

    virtual void encoder::set_symbol(
        uint32_t index, const uint8_t* data, uint32_t size)
    {
        m_wrapper(index, data, size);
    }

    virtual bool encoder::has_systematic_encoder() const
    {
        return m_wrapper.has_systematic_encoder();
    }

    virtual bool encoder::is_systematic_on() const
    {
        return m_wraper.is_systematic_on();
    }

    virtual void encoder::set_systematic_on()
    {
        m_wrapper.set_systematic_on();
    }

    virtual void encoder::set_systematic_off()
    {
        m_wrapper.set_systematic_off();
    }

    virtual void encoder::read_feedback(uint8_t* feedback)
    {
        m_wrapper.read_feedback(feedback);
    }
}
