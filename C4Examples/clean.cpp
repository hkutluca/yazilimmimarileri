#include <cstdint>
#include <vector>
#include <memory>

class User;
struct RecognitionData {
  int32_t id=0;
};

class StatusData;
class DoorInterface {
  public:
  void OpenDoor(int id) {}
};

// outbound
class RecognitionResultInterface {
public:
  RecognitionResultInterface() = default;
  virtual ~RecognitionResultInterface() = default;
  virtual void SuccessfulRecognition(RecognitionData data) = 0;
  virtual void IncompleteSoundData(StatusData status) = 0;
};

// outbound

class DataBaseInterface {
public:
  DataBaseInterface();
   virtual ~DataBaseInterface();
  virtual void GetMetaData() = 0;
  virtual void GetUserHistory(User user) = 0;
};

// module interface inbound
class VoiceRecogniton {
public:
  VoiceRecogniton();
  void Init(RecognitionResultInterface &, DataBaseInterface &);
  void Recognise(std::vector<uint8_t> data);
};

// Implementation

class PosgreSQLDataBaseInterface : public DataBaseInterface {
public:
  PosgreSQLDataBaseInterface();
  virtual ~PosgreSQLDataBaseInterface();
   void GetMetaData() override;
   void GetUserHistory(User user) override;

private:
  DoorInterface door_interface_;
};


// Implementation

class RecognitionResultInterfaceImpl : public RecognitionResultInterface {
public:
  explicit RecognitionResultInterfaceImpl(const std::shared_ptr<DoorInterface>& door_interface)
      : door_interface_(door_interface){};
  void SuccessfulRecognition(RecognitionData data) override;
  void IncompleteSoundData(StatusData status) override;

private:
  std::shared_ptr<DoorInterface> door_interface_;
};
void RecognitionResultInterfaceImpl::SuccessfulRecognition(RecognitionData data) {
  // Send command to open door
  door_interface_->OpenDoor(data.id);
}

int main() {
  auto door_interface = std::make_shared<DoorInterface>();

  RecognitionResultInterfaceImpl recognition_result_interface{door_interface};

  PosgreSQLDataBaseInterface db_interface;

 
  auto voice_recognition = std::make_shared<VoiceRecogniton>();
 
  voice_recognition->Init(recognition_result_interface,db_interface);
}
