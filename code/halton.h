#pragma once
 
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <cmath>
 
namespace quasiMonte {
	struct halton_sequence_engine {
	public:
		typedef double result_type;
 
		halton_sequence_engine(): m_index(1), m_base(2) {}
		halton_sequence_engine(uint32_t index): m_index(index), m_base(2) {}
		halton_sequence_engine(uint32_t index, uint32_t base)
			: m_index(index), m_base(base) {}
 
		result_type operator()() {
			result_type result = 0;
			result_type f = 1 / static_cast<result_type>(m_base);
			uint32_t i = m_index;
			while(i > 0) {
				const uint32_t div_i_base = i / m_base;
				const uint32_t mod_i_base = i % m_base;
				result = result + f*mod_i_base;
				i = div_i_base;
				f = f / m_base;
			}
			++m_index;
			return result;
		}
 
		void seed(uint32_t index) { m_index = index; }
 
		static result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return 0; }
		static result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () { return 1; }
	private:
		uint32_t m_index;
		uint32_t m_base;
	};
}