/****************************************************************

  Generated by Eclipse Cyclone DDS IDL to CXX Translator
  File name: /home/vicon-ws/src/vicon_bridge2/vicon_bridge2/Pose6D.idl
  Source: Pose6D.hpp
  Cyclone DDS: v0.11.0

*****************************************************************/
#ifndef DDSCXX_POSE6D_HPP_AE40DB48439BF73A5F6FF6BFA7B9A025
#define DDSCXX_POSE6D_HPP_AE40DB48439BF73A5F6FF6BFA7B9A025

#include <utility>
#include <ostream>
#include <cstdint>
#include <array>

namespace vicon_bridge2
{
class Pose6D
{
private:
 uint64_t stamp_nano_secs_ = 0;
 std::array<double, 7> q_ = { };
 std::array<double, 3> t_ = { };

public:
  Pose6D() = default;

  explicit Pose6D(
    uint64_t stamp_nano_secs,
    const std::array<double, 7>& q,
    const std::array<double, 3>& t) :
    stamp_nano_secs_(stamp_nano_secs),
    q_(q),
    t_(t) { }

  uint64_t stamp_nano_secs() const { return this->stamp_nano_secs_; }
  uint64_t& stamp_nano_secs() { return this->stamp_nano_secs_; }
  void stamp_nano_secs(uint64_t _val_) { this->stamp_nano_secs_ = _val_; }
  const std::array<double, 7>& q() const { return this->q_; }
  std::array<double, 7>& q() { return this->q_; }
  void q(const std::array<double, 7>& _val_) { this->q_ = _val_; }
  void q(std::array<double, 7>&& _val_) { this->q_ = std::move(_val_); }
  const std::array<double, 3>& t() const { return this->t_; }
  std::array<double, 3>& t() { return this->t_; }
  void t(const std::array<double, 3>& _val_) { this->t_ = _val_; }
  void t(std::array<double, 3>&& _val_) { this->t_ = std::move(_val_); }

  bool operator==(const Pose6D& _other) const
  {
    (void) _other;
    return stamp_nano_secs_ == _other.stamp_nano_secs_ &&
      q_ == _other.q_ &&
      t_ == _other.t_;
  }

  bool operator!=(const Pose6D& _other) const
  {
    return !(*this == _other);
  }

};

std::ostream& operator<<(std::ostream& os, Pose6D const& rhs);

} //namespace vicon_bridge2

#include "dds/topic/TopicTraits.hpp"
#include "org/eclipse/cyclonedds/topic/datatopic.hpp"

namespace org {
namespace eclipse {
namespace cyclonedds {
namespace topic {

template <> constexpr const char* TopicTraits<::vicon_bridge2::Pose6D>::getTypeName()
{
  return "vicon_bridge2::Pose6D";
}

template <> constexpr bool TopicTraits<::vicon_bridge2::Pose6D>::isKeyless()
{
  return true;
}

#ifdef DDSCXX_HAS_TYPELIB
template<> constexpr unsigned int TopicTraits<::vicon_bridge2::Pose6D>::type_map_blob_sz() { return 334; }
template<> constexpr unsigned int TopicTraits<::vicon_bridge2::Pose6D>::type_info_blob_sz() { return 100; }
template<> inline const uint8_t * TopicTraits<::vicon_bridge2::Pose6D>::type_map_blob() {
  alignas(4) static const uint8_t blob[] = {
 0x72,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00,  0xf1,  0xa0,  0xf4,  0xd6,  0x97,  0x8b,  0x38,  0x8d, 
 0x25,  0x00,  0xf7,  0xea,  0x8a,  0x79,  0x60,  0x00,  0x5a,  0x00,  0x00,  0x00,  0xf1,  0x51,  0x01,  0x00, 
 0x01,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x4a,  0x00,  0x00,  0x00,  0x03,  0x00,  0x00,  0x00, 
 0x0b,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x01,  0x00,  0x08,  0x5b,  0xa3,  0x39,  0x50,  0x00, 
 0x16,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00,  0x01,  0x00,  0x90,  0xf3,  0x01,  0x00,  0x00,  0x00, 
 0x01,  0x00,  0x00,  0x00,  0x07,  0x0a,  0x76,  0x94,  0xf4,  0xa6,  0x00,  0x00,  0x16,  0x00,  0x00,  0x00, 
 0x02,  0x00,  0x00,  0x00,  0x01,  0x00,  0x90,  0xf3,  0x01,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00, 
 0x03,  0x0a,  0xe3,  0x58,  0xef,  0xa4,  0x00,  0x00,  0xac,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00, 
 0xf2,  0xa3,  0x34,  0xfe,  0x58,  0x8e,  0x68,  0x97,  0xa6,  0x39,  0x3a,  0x18,  0xce,  0x73,  0x2e,  0x00, 
 0x94,  0x00,  0x00,  0x00,  0xf2,  0x51,  0x01,  0x00,  0x1e,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00, 
 0x16,  0x00,  0x00,  0x00,  0x76,  0x69,  0x63,  0x6f,  0x6e,  0x5f,  0x62,  0x72,  0x69,  0x64,  0x67,  0x65, 
 0x32,  0x3a,  0x3a,  0x50,  0x6f,  0x73,  0x65,  0x36,  0x44,  0x00,  0x00,  0x00,  0x68,  0x00,  0x00,  0x00, 
 0x03,  0x00,  0x00,  0x00,  0x1e,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x01,  0x00,  0x08,  0x00, 
 0x10,  0x00,  0x00,  0x00,  0x73,  0x74,  0x61,  0x6d,  0x70,  0x5f,  0x6e,  0x61,  0x6e,  0x6f,  0x5f,  0x73, 
 0x65,  0x63,  0x73,  0x00,  0x00,  0x00,  0x00,  0x00,  0x1c,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00, 
 0x01,  0x00,  0x90,  0xf3,  0x01,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00,  0x07,  0x0a,  0x00,  0x00, 
 0x02,  0x00,  0x00,  0x00,  0x71,  0x00,  0x00,  0x00,  0x1c,  0x00,  0x00,  0x00,  0x02,  0x00,  0x00,  0x00, 
 0x01,  0x00,  0x90,  0xf3,  0x01,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00,  0x03,  0x0a,  0x00,  0x00, 
 0x02,  0x00,  0x00,  0x00,  0x74,  0x00,  0x00,  0x00,  0x22,  0x00,  0x00,  0x00,  0x01,  0x00,  0x00,  0x00, 
 0xf2,  0xa3,  0x34,  0xfe,  0x58,  0x8e,  0x68,  0x97,  0xa6,  0x39,  0x3a,  0x18,  0xce,  0x73,  0x2e,  0xf1, 
 0xa0,  0xf4,  0xd6,  0x97,  0x8b,  0x38,  0x8d,  0x25,  0x00,  0xf7,  0xea,  0x8a,  0x79,  0x60, };
  return blob;
}
template<> inline const uint8_t * TopicTraits<::vicon_bridge2::Pose6D>::type_info_blob() {
  alignas(4) static const uint8_t blob[] = {
 0x60,  0x00,  0x00,  0x00,  0x01,  0x10,  0x00,  0x40,  0x28,  0x00,  0x00,  0x00,  0x24,  0x00,  0x00,  0x00, 
 0x14,  0x00,  0x00,  0x00,  0xf1,  0xa0,  0xf4,  0xd6,  0x97,  0x8b,  0x38,  0x8d,  0x25,  0x00,  0xf7,  0xea, 
 0x8a,  0x79,  0x60,  0x00,  0x5e,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x04,  0x00,  0x00,  0x00, 
 0x00,  0x00,  0x00,  0x00,  0x02,  0x10,  0x00,  0x40,  0x28,  0x00,  0x00,  0x00,  0x24,  0x00,  0x00,  0x00, 
 0x14,  0x00,  0x00,  0x00,  0xf2,  0xa3,  0x34,  0xfe,  0x58,  0x8e,  0x68,  0x97,  0xa6,  0x39,  0x3a,  0x18, 
 0xce,  0x73,  0x2e,  0x00,  0x98,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x04,  0x00,  0x00,  0x00, 
 0x00,  0x00,  0x00,  0x00, };
  return blob;
}
#endif //DDSCXX_HAS_TYPELIB

} //namespace topic
} //namespace cyclonedds
} //namespace eclipse
} //namespace org

namespace dds {
namespace topic {

template <>
struct topic_type_name<::vicon_bridge2::Pose6D>
{
    static std::string value()
    {
      return org::eclipse::cyclonedds::topic::TopicTraits<::vicon_bridge2::Pose6D>::getTypeName();
    }
};

}
}

REGISTER_TOPIC_TYPE(::vicon_bridge2::Pose6D)

namespace org{
namespace eclipse{
namespace cyclonedds{
namespace core{
namespace cdr{

template<>
const propvec &get_type_props<::vicon_bridge2::Pose6D>();

namespace {
  static const volatile propvec &properties___vicon_bridge2__Pose6D = get_type_props<::vicon_bridge2::Pose6D>();
}

template<typename T, std::enable_if_t<std::is_base_of<cdr_stream, T>::value, bool> = true >
bool write(T& streamer, const ::vicon_bridge2::Pose6D& instance, const entity_properties_t *props) {
  (void)instance;
  member_id_set member_ids;
  if (!streamer.start_struct(*props))
    return false;
  auto prop = streamer.first_entity(props);
  while (prop) {
    switch (prop->m_id) {
      case 0:
      if (!streamer.start_member(*prop))
        return false;
      if (!write(streamer, instance.stamp_nano_secs()))
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 1:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!write(streamer, instance.q()[0], instance.q().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 2:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!write(streamer, instance.t()[0], instance.t().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
    }
    prop = streamer.next_entity(prop);
  }
  return streamer.finish_struct(*props, member_ids);
}

template<typename S, std::enable_if_t<std::is_base_of<cdr_stream, S>::value, bool> = true >
bool write(S& str, const ::vicon_bridge2::Pose6D& instance, key_mode key) {
  const auto &props = get_type_props<::vicon_bridge2::Pose6D>();
  str.set_mode(cdr_stream::stream_mode::write, key);
  return write(str, instance, props.data()); 
}

template<typename T, std::enable_if_t<std::is_base_of<cdr_stream, T>::value, bool> = true >
bool read(T& streamer, ::vicon_bridge2::Pose6D& instance, const entity_properties_t *props) {
  (void)instance;
  member_id_set member_ids;
  if (!streamer.start_struct(*props))
    return false;
  auto prop = streamer.first_entity(props);
  while (prop) {
    switch (prop->m_id) {
      case 0:
      if (!streamer.start_member(*prop))
        return false;
      if (!read(streamer, instance.stamp_nano_secs()))
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 1:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!read(streamer, instance.q()[0], instance.q().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 2:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!read(streamer, instance.t()[0], instance.t().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
    }
    prop = streamer.next_entity(prop);
  }
  return streamer.finish_struct(*props, member_ids);
}

template<typename S, std::enable_if_t<std::is_base_of<cdr_stream, S>::value, bool> = true >
bool read(S& str, ::vicon_bridge2::Pose6D& instance, key_mode key) {
  const auto &props = get_type_props<::vicon_bridge2::Pose6D>();
  str.set_mode(cdr_stream::stream_mode::read, key);
  return read(str, instance, props.data()); 
}

template<typename T, std::enable_if_t<std::is_base_of<cdr_stream, T>::value, bool> = true >
bool move(T& streamer, const ::vicon_bridge2::Pose6D& instance, const entity_properties_t *props) {
  (void)instance;
  member_id_set member_ids;
  if (!streamer.start_struct(*props))
    return false;
  auto prop = streamer.first_entity(props);
  while (prop) {
    switch (prop->m_id) {
      case 0:
      if (!streamer.start_member(*prop))
        return false;
      if (!move(streamer, instance.stamp_nano_secs()))
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 1:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!move(streamer, instance.q()[0], instance.q().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 2:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!move(streamer, instance.t()[0], instance.t().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
    }
    prop = streamer.next_entity(prop);
  }
  return streamer.finish_struct(*props, member_ids);
}

template<typename S, std::enable_if_t<std::is_base_of<cdr_stream, S>::value, bool> = true >
bool move(S& str, const ::vicon_bridge2::Pose6D& instance, key_mode key) {
  const auto &props = get_type_props<::vicon_bridge2::Pose6D>();
  str.set_mode(cdr_stream::stream_mode::move, key);
  return move(str, instance, props.data()); 
}

template<typename T, std::enable_if_t<std::is_base_of<cdr_stream, T>::value, bool> = true >
bool max(T& streamer, const ::vicon_bridge2::Pose6D& instance, const entity_properties_t *props) {
  (void)instance;
  member_id_set member_ids;
  if (!streamer.start_struct(*props))
    return false;
  auto prop = streamer.first_entity(props);
  while (prop) {
    switch (prop->m_id) {
      case 0:
      if (!streamer.start_member(*prop))
        return false;
      if (!max(streamer, instance.stamp_nano_secs()))
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 1:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!max(streamer, instance.q()[0], instance.q().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
      case 2:
      if (!streamer.start_member(*prop))
        return false;
      if (!streamer.start_consecutive(true, true))
        return false;
      if (!max(streamer, instance.t()[0], instance.t().size()))
        return false;
      if (!streamer.finish_consecutive())
        return false;
      if (!streamer.finish_member(*prop, member_ids))
        return false;
      break;
    }
    prop = streamer.next_entity(prop);
  }
  return streamer.finish_struct(*props, member_ids);
}

template<typename S, std::enable_if_t<std::is_base_of<cdr_stream, S>::value, bool> = true >
bool max(S& str, const ::vicon_bridge2::Pose6D& instance, key_mode key) {
  const auto &props = get_type_props<::vicon_bridge2::Pose6D>();
  str.set_mode(cdr_stream::stream_mode::max, key);
  return max(str, instance, props.data()); 
}

} //namespace cdr
} //namespace core
} //namespace cyclonedds
} //namespace eclipse
} //namespace org

#endif // DDSCXX_POSE6D_HPP_AE40DB48439BF73A5F6FF6BFA7B9A025
