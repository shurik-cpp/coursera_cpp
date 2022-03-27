#pragma once

namespace RAII {

template <typename Provider>
class Booking {

	using Id = typename Provider::BookingId;

private:
	Provider* provider;
	Id id;

public:
	Booking(Provider* p, Id i)
		: provider(p)
		, id(i)
	{
	}

	Booking(Booking&& other)
		: provider(other.provider)
		, id(other.id)
	{
		other.provider = nullptr;
	}

	Booking() = delete;
	Booking(const Booking&) = delete;
	Booking& operator=(const Booking&) = delete;

	Booking& operator=(Booking&& other) {
		provider = other.provider;
		id = other.id;
		other.provider = nullptr;

		return *this;
	}

	~Booking() {
		if (provider != nullptr) {
			provider->CancelOrComplete(*this);
		}
	}
};

} // end namespace RAII
