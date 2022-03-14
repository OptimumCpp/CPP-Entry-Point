/// This header file defines a very low-cost and error-safe library for basic storage and treatment of
/// program command line arguments.
/// mailto:farid.mehrabi@gmail.com

#ifndef		COMMAND_LINE_HPP
#define		COMMAND_LINE_HPP
#include	<span>
#include	<string_view>

/// <summary>
/// this namespace is upposed to be replaced with 'boost' or 'std', iff adopted as part the above 
/// libs - by proper authorities. For the time being the 'fm' suffix in the namespace identifier 
/// refers the signature and initials of the author.
/// </summary>
namespace lib_fm {

	using namespace std;

	/// <summary>
	/// this class is supposed to wrap arguments of the main function in an ideally NOOP fashion and provide
	/// a smooth and as error-free as possible API 
	/// </summary>
	/// <param name="ch_type">
	/// character type to be used
	/// </param>
	/// <param name="ext">
	/// defines the extent(count) of arguments. By default ('std::dynamic_extent') the count is evaluated
	/// at runtime. 
	/// </param>
	/// <param name="traits">
	/// coddec and conversions used by std::basic_string_view
	/// </param>
	template<typename ch_type, size_t ext = dynamic_extent, typename traits = char_traits<ch_type>>
	struct basic_command_line
		: span<ch_type* const, ext>
	{
		//important type aliases:
		using base_type = span<ch_type* const, ext>;
		using char_type = ch_type;
		using char_traits = traits;
		using legacy_reference = typename base_type::reference;
		using legacy_element_type = typename base_type::element_type;
		using legacy_pointer = typename base_type::pointer;
		using command_pointer = char_type**;
		typedef const char_type  *const*pointer, *const*const_pointer;
		
		/// <summary>
		/// ='std::basic_string_view'.
		/// Result of 'front', 'back', 'operator[index]' and dereferencing 'basic_command_line::iterator'
		/// </summary>
		typedef const basic_string_view<char_type, char_traits> argument_type, value_type, element_type, const_element_type;

		template <typename base_iterator> struct basic_iterator;
		using iterator = basic_iterator<typename base_type::iterator>;
		using reverse_iterator = basic_iterator<typename base_type::reverse_iterator>;

		//unaffected 'span' members: 
		using typename base_type::difference_type;
		using typename base_type::size_type;
		using base_type::extent;
		using base_type::size;
		using base_type::empty;
		using base_type::size_bytes;

		//forwarding to 'span::span' constructors:
		using span<ch_type* const, ext>::span;

		explicit(extent != dynamic_extent)
			/// <summary>
			/// The only none forwarded constructor defined within the class
			/// </summary>
			/// <param name="count">reads the count 'argc' of arguments from 'main' function </param>
			/// <param name="first">reads the'argv' argument list from 'main' function</param>
			/// <returns>creates a light-weight object to mannage command line argumnts</returns>
			constexpr basic_command_line(int count, command_pointer first) noexcept
			: base_type{ first, count }
		{};

		//iterator to first command line argument:
		constexpr iterator begin() const noexcept
		{
			return { this->base_type::begin() };
		};
		//iterator to first invalid location past the last command line argument:
		constexpr iterator end() const noexcept
		{
			return { this->base_type::end() };
		};
		//reverse iterator to last command line argument:
		constexpr reverse_iterator rbegin() const noexcept
		{
			return { this->base_type::rbegin() };
		};
		//reverse iterator to first invalid location before the first command line argument:
		constexpr reverse_iterator rend() const noexcept
		{
			return { this->base_type::rend() };
		};

		friend auto as_bytes(basic_command_line cmd)noexcept
		{
			return static_cast<base_type>(cmd);
		};
		
		/// <summary>
		/// Retrives the last argument from command line
		/// </summary>
		/// <returns>
		/// A veiw of 'basic_command_line::argument_type' to the last command line argument
		/// </returns>
		constexpr argument_type back() const noexcept
		{
			return { this->base_type::back() };
		};
		/// <summary>
		/// Retrives the first argument from command line
		/// </summary>
		/// <returns>
		/// A veiw of 'basic_command_line::argument_type' to the first command line argument
		/// </returns>
		constexpr argument_type front() const noexcept
		{
			return { this->base_type::front() };
		};

		constexpr auto operator[](size_type offset) const
		{
			return begin()[offset];
		};

		constexpr const_pointer data() const noexcept
		{
			return this->base_type::data();
		};

		///<summary> Hides 'span::subspann'.</summary>
		///<param name="offset">
		///Beginning argument in the new view with respect to current view.</param>
		///<param name="count">
		///Requested count of arguments in new view. Defaults to max('std::dynamic_extent')
		///</param>
		///<returns>
		///A new list of 'count' command line arguments beginning at 'offset' from this
		///</returns>
		constexpr auto subspan(size_type offset, size_type count = dynamic_extent) const noexcept
		{
			return from_span(this->base_type::subspan(offset, count));
		};
	
		///<summary> Hides 'span::subspann'.</summary>
		///<param name="offset">
		///'constexpr' start argument in the new view with respect to current view.</param>
		///<param name="count">
		///'constexpr' requested count of arguments in new view.
		/// Default is max('std::dynamic_extent')
		///</param>
		///<returns>
		///A new list of 'count' command line arguments beginning at 'offset' from this
		///</returns>
		template <size_t offset, size_t count = dynamic_extent>
		constexpr auto subspan() const noexcept
		{
			return from_span(this->base_type::subspan<offset, count>());
		};

		///<summary> Hides 'span::first'.</summary>
		///<param name="count">
		///Requested count of arguments in new view.
		///</param>
		///<returns>
		///A new list of 'count' left-most command line arguments
		///</returns>
		constexpr auto first(size_type count) const noexcept
		{
			return  from_span(this->base_type::first(count));
		};
		///<summary> Hides 'span::first'.</summary>
		///<param name="count">
		///'constexpr' requested count of arguments in new view.
		///</param>
		///<returns>
		///A new list of 'count' left-most command line arguments
		///</returns>
		template <size_t count>
		constexpr auto first() const noexcept
		{
			return  from_span(this->base_type::first<count>());
		};

		///<summary> Hides 'span::last'.</summary>
		///<param name="count">
		///Requested count of arguments in new view.
		///</param>
		///<returns>
		///A new list of 'count' right-most command line arguments
		///</returns>
		constexpr auto last(size_type count) const noexcept
		{
			return  from_span(this->base_type::last(count));
		};
		///<summary> Hides 'span::last'.</summary>
		///<param name="count">
		///'constexpr' requested count of arguments in new view.
		///</param>
		///<returns>
		///A new list of 'count' right-most command line arguments
		///</returns>
		template <size_t count>
		constexpr auto last() const noexcept
		{
			return  from_span(this->base_type::last<count>());
		};

		/// <summary>
		/// Wraps and decorates iterators inherited from 'std::span'
		/// This is actually a hack and should be modified
		/// </summary>
		/// <param name="base_iterator">
		/// ='std::span::iterator' or 'std::span::const_iterator'
		/// </param>
		template <typename base_iterator>
		struct basic_iterator
			: base_iterator
		{
			typedef const argument_type value_type, reference_type, const_reference_type;

			typedef struct pointer const_pointer;

			auto operator<=>(basic_iterator const& right)const noexcept = default;

			constexpr auto operator[](size_type offset) const
			{
				return *(*this + offset);
			};

			constexpr const_reference_type operator*() const
			{
				return { base_iterator::operator*() };
			};

			constexpr auto operator->() const
			{
				return pointer{ .value{**this} };
			};

			constexpr auto& operator++() noexcept
			{
				base_iterator::operator++();
				return *this;
			};
			constexpr basic_iterator operator--() noexcept
			{
				base_iterator::operator--();
				return *this;
			};
			constexpr basic_iterator operator++(int) noexcept
			{
				return { base_iterator::operator++(0) };
			};
			constexpr basic_iterator operator--(int) noexcept
			{
				return { base_iterator::operator--(0) };
			};

			constexpr basic_iterator operator+=(size_type add) noexcept
			{
				return { base_iterator {*this} += add };
			};

			constexpr basic_iterator operator-=(size_type sub) noexcept
			{
				return { base_iterator {*this} -= sub };
			};

			constexpr basic_iterator operator+(size_type add) const noexcept
			{
				return { base_iterator {*this} + add };
			};

			constexpr basic_iterator operator-(size_type sub) const noexcept
			{
				return { base_iterator {*this} - sub };
			};

			/// <summary>
			/// a smart ptr that converts null-terminated strings to 'std::string_view's on the fly. A fancy ptr to be used
			/// as the result of indirection ('basic_iterator::operator->').
			/// <TODO>Move this outside the 'basic_comand_line' to reduce compiler load; It doesn't depent on 'extent'</TODO>
			/// </summary>
			struct pointer {
				argument_type const value;
				constexpr auto operator->()const noexcept
				{
					return &value;
				};
			};
		private:
			friend typename basic_command_line;
			constexpr basic_iterator(base_iterator  val) noexcept
				:base_iterator{ move(val) }
			{};
		};//!basic_iterator

	private:

		using typename base_type::reference;
		using typename base_type::const_reference;

		/// <summary>
		/// Changes the view from a list of null-terminated strings to a list of 'std::basic_string_view'
		/// <TODO>Move this outside the 'basic_comand_line' to reduce compiler load; It doesn't depent on 'this->extent'</TODO>
		/// </summary>
		/// <param name="source"> result of 'std::span::first', 'std::span::last', 'std::span::subspan' </param>
		/// <returns>A subview of 'std::basic_string_view'  to the command line arguments</returns>
		template<size_t oth_ext>
		static constexpr auto from_span(span<legacy_element_type, oth_ext> source) noexcept
		{
			return basic_command_line<char_type,oth_ext,char_traits> { source.data(),source.size() };
		}

	};//!basic_command_line

	using command_line = basic_command_line<char>;
};//!lib_fm

#endif //!	COMMAND_LINE_HPP
