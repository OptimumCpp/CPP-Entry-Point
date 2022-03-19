/// This header file defines a very low-cost and error-safe library for basic storage and treatment of
/// program command line arguments.
/// mailto:farid.mehrabi@gmail.com

#ifndef		COMMAND_LINE_HPP
#define		COMMAND_LINE_HPP
//#include	<map>
#include	<span>
#include	<ranges>
#include	<string_view>

/// <summary>
/// this namespace is upposed to be replaced with 'boost' or 'std', iff adopted as part the above 
/// libs - by proper authorities. For the time being the 'fm' suffix in the namespace identifier 
/// refers the signature and initials of the author.
/// </summary>
namespace lib_fm {
	namespace details {
		template<typename char_traits, typename char_type, std::size_t extent>
		constexpr auto command_line_func(std::span<char_type* const, extent> cmd) noexcept
		{
			return std::views::transform(cmd, [](auto strptr) {return std::basic_string_view<char_type, char_traits>{strptr}; });
		};

		template<typename char_traits, typename char_type>
		constexpr auto environment_func(std::span<char_type* const> cmd) noexcept
		{
			return std::views::transform(command_line_func<char_traits>(cmd), [](std::basic_string_view<char_type, char_traits> strview){
				auto const cut = strview.find('=');
				return std::make_pair(strview.substr(0,cut), strview.substr(cut+1));
			});
		};

		template<
			auto func,
			typename arg_type,
			typename base = decltype(func(std::declval<arg_type>()))
		> struct from_result
			: base
		{
		protected:
			using argument_list = arg_type;
			using base::base;
			constexpr from_result(argument_list args) noexcept
				: base{ constructor(args) }
			{};
		private:
			constexpr static auto constructor = func;
		};//! from_result
	};//! details

	/// <summary>
	/// this class is supposed to wrap arguments of the main function in an ideally noop fashion and provide
	/// a smooth and as error-free as possible api 
	/// </summary>
	/// <param name="ch_type">
	/// character type to be used
	/// </param>
	/// <param name="ext">
	/// defines the extent(count) of arguments. by default ('std::dynamic_extent') the count is evaluated
	/// at runtime. 
	/// </param>
	/// <param name="traits">
	/// coddec and conversions used by std::basic_string_view
	/// </param>
	template<
		typename ch_type=char,
		typename traits = std::char_traits<ch_type>,
		std::size_t ext = std::dynamic_extent
	>struct basic_main_arguments
		: details::from_result<details::command_line_func<traits, ch_type, ext>, std::span<ch_type* const>>
	{
	private:
		using base = details::from_result<details::command_line_func<traits, ch_type, ext>, std::span<ch_type* const>>;
	public:
		auto constexpr static extent = ext;
		using char_type = ch_type;
		using char_traits = traits;
		using element_type = typename std::basic_string_view<char_type, char_traits>;
		using raw_argument_list = char_type *const*;
		using typename base::argument_list;

		constexpr basic_main_arguments(argument_list args) noexcept
			: base{ args }
		{};

	private:

		friend class main_forwarder;

		constexpr basic_main_arguments(int count, raw_argument_list args) noexcept
			: base{ { args,static_cast<std::size_t>(count) } }
		{};

	};//! basic_command_line

	template<
		typename ch_type = char,
		typename traits = std::char_traits<ch_type>
	>struct basic_environment
		: details::from_result<details::environment_func<traits, ch_type>, std::span<ch_type* const>>
	{
	private:
		using base = details::from_result<details::environment_func<traits, ch_type>, std::span<ch_type* const>>;
	public:
		using char_type = ch_type;
		using char_traits = traits;
		typedef std::basic_string_view<char_type, char_traits> key_type, value_type;
		using raw_argument_list = char_type* const*;
		using typename base::argument_list;

		constexpr basic_environment(argument_list args) noexcept
			: base{ args }
		{};

	public:
		constexpr auto find(key_type const key) const noexcept
		{
			auto static constexpr projection = [](char_type ch) {return std::is_same_v<ch_type, char> ? toupper(ch) : ch ; };
			return (*this) | std::views::filter([key](auto const& pair) {
				return std::ranges::equal(pair.first, key, {}, projection, projection);
				});
		};
		using base::operator[];
		constexpr auto operator[](key_type const key)const noexcept {
			return find(key) | std::views::values;
		};

	private:

		friend class main_forwarder;

		constexpr basic_environment(raw_argument_list args) noexcept
			: base{ { args, std::find(args,args + std::numeric_limits<int>::max(),nullptr)} }
		{};
	};


	using main_arguments = basic_main_arguments<>;
	using environment = basic_environment<>;
};//! lib_fm

#endif //!	COMMAND_LINE_HPP
