/* Многие программы создаются для пакетной обработки большого числа однородных записей.
 * Часто при этом обработка этих записей может быть разделена на логически самостоятельные этапы,
 * это упрощает совместную разработку новых фич и позволяет легко комбинировать эти этапы в новые конфигурации.
 * Такую обработку можно мысленно вообразить себе как поток объектов, идущих по конвейеру от одного обработчика к другому.
 * В этой задаче вам предстоит закончить реализацию такого конвейера.
 *
 * Основная идея конвейера в том, чтобы использовать функции, "поглощающие" объекты и вызывающие друг друга:
 * void ConsumeObject(unique_ptr<SomeObject> obj) {
 * 	 // обработка
 *   ConsumeObject2(move(obj));  // теряем владение объектом
 * }
*/
#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// В этой задаче вам предлагается разработать конвейер обработчиков электронных писем:
struct Email {
	string from;
	string to;
	string body;
};

istream& operator>>(istream& in, Email& email) {
	getline(in, email.from);
	getline(in, email.to);
	getline(in, email.body);
	return in;
}
ostream& operator<<(ostream& out, const Email& email) {
	out << email.from << '\n' << email.to << '\n' << email.body;
	return out;
}
// Worker метод SetNext должен принимать во владение следующий обработчик из цепочки
// метод PassOn должен вызывать метод Process следующего обработчика, если он был установлен
class Worker {
public:
	virtual ~Worker() = default;
	virtual void Process(unique_ptr<Email> email) = 0;
	virtual void Run() {
		// только первому worker-у в пайплайне нужно реализовать этот метод, т.е для класса Reader : public Worker
		throw logic_error("Unimplemented");
	}

	void SetNext(unique_ptr<Worker> next) {
		next_ = move(next);
	}
protected:
	// реализации должны вызывать PassOn, чтобы передать объект дальше
	// по цепочке обработчиков
	void PassOn(unique_ptr<Email> email) const {
		if (next_) {
			next_->Process(move(email));
		}
	}

private:
	unique_ptr<Worker> next_;
};

// Reader конструктор должен принимать входной поток (istream&), из которого нужно читать сообщения
// метод Run должен читать из входного потока все e-mail'ы и передавать дальше каждый из них.
// Один e-mail представляется во входном потоке полями from, to, body, каждое из которых находится на своей строке.
class Reader : public Worker {
public:
	explicit Reader(istream& in)
		: input(in) {}

	void Process(unique_ptr<Email> email) override {}

	void Run() override {
		Email email;
		while (input >> email) {
			PassOn(make_unique<Email>(move(email)));
		}
	}

private:
	istream& input;
};

// Filter конструктор должен принимать предикат типа function<bool(const Email&)>
// метод Process должен передавать дальше только сообщения, удовлетворяющие предикату
class Filter : public Worker {
public:
	using Function = function<bool(const Email&)>;
	explicit Filter(Function foo)
		: func(move(foo)) {}

	void Process(unique_ptr<Email> email) override {
		if (func(*email)) {
			PassOn(move(email));
		}
	}

private:
	Function func;
};

// Copier конструктор должен принимать строку-адрес получателя
// метод Process должен передавать сообщение как исходному(текущему) получателю, так и указанному в конструкторе (recipient_).
// В случае, если они совпадают, дублировать сообщение не нужно
class Copier : public Worker {
public:
	explicit Copier(const string& recipient)
		: recipient_(recipient) {}

	void Process(unique_ptr<Email> email) override {
		if (recipient_ == email->to) {
			PassOn(move(email));
		} else {
			unique_ptr<Email> copy = make_unique<Email>(*email);
			copy->to = recipient_;
			PassOn(move(email));
			PassOn(move(copy));
		}
	}

private:
	string recipient_;
};

// Sender конструктор должен принимать поток для записи сообщений
// метод Process должен записывать сообщения в поток в том же формате, в котором они были прочитаны
class Sender : public Worker {
public:
	explicit Sender(ostream& output)
		: out(output) {}

	void Process(unique_ptr<Email> email) override {
		out << *email << '\n';
		PassOn(move(email));
	}

private:
	ostream& out;
};

// Конструктор должен инициализировать цепочку обработчиков обработчиком Reader с переданным потоком.
class PipelineBuilder {
public:
	// добавляет в качестве первого обработчика Reader
	explicit PipelineBuilder(istream& in) {
		workers_ptr.push_back(make_unique<Reader>(in));
	}

	// добавляет новый обработчик Filter
	PipelineBuilder& FilterBy(Filter::Function filter) {
		workers_ptr.push_back(make_unique<Filter>(filter));
		return *this;
	}

	// добавляет новый обработчик Copier
	PipelineBuilder& CopyTo(string recipient) { // recipient - получатель
		workers_ptr.push_back(make_unique<Copier>(recipient));
		return *this;
	}

	// добавляет новый обработчик Sender
	PipelineBuilder& Send(ostream& out) {
		workers_ptr.push_back(make_unique<Sender>(out));
		return *this;
	}

	// строит цепочку с помощью метода Worker::SetNext и возвращает первый обработчик в построенной цепочке
	unique_ptr<Worker> Build() {
		for (size_t i = workers_ptr.size() - 1; i > 0; --i) {
			workers_ptr[i - 1]->SetNext(move(workers_ptr[i]));
		}

		return move(workers_ptr[0]);
	}

private:
	vector<unique_ptr<Worker>> workers_ptr;
};


void TestSanity() {
	string input = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"ralph@example.com\n"
		"erich@example.com\n"
		"I do not make mistakes of that kind\n"
	);
	istringstream inStream(input);
	ostringstream outStream;

	PipelineBuilder builder(inStream);
	builder.FilterBy([](const Email& email) {
		return email.from == "erich@example.com";
	});
	builder.CopyTo("richard@example.com");
	builder.Send(outStream);
	auto pipeline = builder.Build();

	pipeline->Run();

	string expectedOutput = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"erich@example.com\n"
		"richard@example.com\n"
		"Are you sure you pressed the right button?\n"
	);

	ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSanity);
	return 0;
}
