#pragma once

#include <cstdint>
#include <algorithm>

namespace x69::tmnl
{

	struct Position
	{
		friend inline constexpr bool operator==(const Position& lhs, const Position& rhs) noexcept = default;
		friend inline constexpr bool operator!=(const Position& lhs, const Position& rhs) noexcept = default;

		int x = 0;
		int y = 0;
	};

	struct Region
	{
		int xMin = 0;
		int yMin = 0;
		int xMax = 0;
		int yMax = 0;

		constexpr Region() noexcept = default;
		constexpr Region(int _xMin, int _yMin, int _xMax, int _yMax) noexcept :
			xMin{ _xMin }, yMin{ _yMin }, xMax{ _xMax }, yMax{ _yMax }
		{};

		constexpr Region(Position _min, Position _max) noexcept :
			Region{ _min.x, _min.y, _max.x, _max.y }
		{};

	};

	class Cursor
	{
	private:
		void clamp_pos() noexcept
		{
			const auto& _begin = this->begin();
			auto& _at = this->at();
			const auto& _end = this->end();
			_at.x = std::clamp(_at.x, _begin.x, _end.x);
			_at.y = std::clamp(_at.y, _begin.y, _end.y);
		};

	public:

		constexpr Position& begin() noexcept { return this->begin_; };
		constexpr const Position& begin() const noexcept { return this->begin_; };
		
		constexpr Position& end() noexcept { return this->end_; };
		constexpr const Position& end() const noexcept { return this->end_; };
		
		constexpr Position& at() noexcept { return this->at_; };
		constexpr const Position& at() const noexcept { return this->at_; };

		// Resets the cursor to the beginning and returns the cursor position prior to reset
		Position reset() noexcept
		{
			auto _out{ this->at() };
			this->at_ = this->begin();
			return _out;
		};

		// Shifts the cursor by (_dx, _dx) and return new cursor position
		Position seek(int _dx, int _dy) noexcept
		{
			auto& _cpos = this->at();
			_cpos.x += _dx;
			_cpos.y += _dy;

			this->clamp_pos();

			return _cpos;
		};

		constexpr Region region() const noexcept
		{
			Region _out{};
			
			const auto& _begin = this->begin();
			const auto& _end = this->end();

			_out.xMin = _begin.x;
			_out.yMin = _begin.y;
			_out.xMax = _end.x;
			_out.yMax = _end.y;

			return _out;
		};

		// Sets the cursor position to (_x, _y) relative to the cursor start
		Position set(int _x, int _y) noexcept
		{
			const auto& _begin = this->begin();
			auto& _at = this->at();

			_at.x = _begin.x + _x;
			_at.y = _begin.y + _y;

			this->clamp_pos();

			return _at;
		};

		void next_line()
		{
			this->at().x = this->begin().x;
			++this->at().y;
		};

		// Advances the cursor forward by n, and adjusts for eol
		auto& advance(size_t n = 1) noexcept
		{
			auto& _at = this->at();
			const auto& _begin = this->begin();
			const auto& _end = this->end();

			for (int i = 0; i != n; ++i)
			{
				++_at.x;
				if (_at.x == _end.x)
				{
					++_at.y;
					_at.x = _begin.x;
				};
			};

			return *this;
		};


		constexpr Cursor() noexcept = default;

		constexpr Cursor(const Position& _begin, const Position& _end, const Position& _at) noexcept :
			begin_{ _begin }, end_{ _end }, at_{ _at }
		{};
		
		constexpr Cursor(const Region& _region, const Position& _at) noexcept :
			Cursor{ { _region.xMin, _region.yMin }, { _region.xMax, _region.yMax }, _at }
		{};
		constexpr Cursor(const Region& _region) noexcept :
			Cursor{ _region, { _region.xMin, _region.yMin } }
		{};

	private:
		Position begin_{ 0, 0 };
		Position end_{ 0, 0 };
		Position at_{ 0, 0 };
	};




};
