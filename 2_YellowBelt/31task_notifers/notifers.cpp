class INotifier {
public:
  virtual void Notify(const string& message) const = 0;
};

// Класс SmsNotifier, который:
// является потомком класса INotifier;
// в конструкторе принимает один параметр типа string — номер телефона;
// переопределяет метод Notify и вызывает из него функцию SendSms.
class SmsNotifier : public INotifier {
public:
  SmsNotifier(const string& phone_number)
      : _phone_number(phone_number) {}

  void Notify(const string& message) const override {
    SendSms(_phone_number, message);
  }

private:
  const string _phone_number;
};

// Класс EmailNotifier, который:
// является потомком класса INotifier;
// в конструкторе принимает один параметр типа string — адрес электронной почты;
// переопределяет метод Notify и вызывает из него функцию SendEmail.
class EmailNotifier : public INotifier {
public:
  EmailNotifier(const string& email_address)
      : _email_address(email_address) {}

  void Notify(const string& message) const override {
    SendEmail(_email_address, message);
  }

private:
  const string _email_address;
};
