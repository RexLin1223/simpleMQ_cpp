// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: customized_message.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_customized_5fmessage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_customized_5fmessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3010000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3010001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_customized_5fmessage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_customized_5fmessage_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_customized_5fmessage_2eproto;
namespace message {
class PublisherMessage;
class PublisherMessageDefaultTypeInternal;
extern PublisherMessageDefaultTypeInternal _PublisherMessage_default_instance_;
class SubscriberMessage;
class SubscriberMessageDefaultTypeInternal;
extern SubscriberMessageDefaultTypeInternal _SubscriberMessage_default_instance_;
class VisitorProperty;
class VisitorPropertyDefaultTypeInternal;
extern VisitorPropertyDefaultTypeInternal _VisitorProperty_default_instance_;
}  // namespace message
PROTOBUF_NAMESPACE_OPEN
template<> ::message::PublisherMessage* Arena::CreateMaybeMessage<::message::PublisherMessage>(Arena*);
template<> ::message::SubscriberMessage* Arena::CreateMaybeMessage<::message::SubscriberMessage>(Arena*);
template<> ::message::VisitorProperty* Arena::CreateMaybeMessage<::message::VisitorProperty>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace message {

enum VisitorType : int {
  unknown = 0,
  publisher = 1,
  subscriber = 2,
  VisitorType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  VisitorType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool VisitorType_IsValid(int value);
constexpr VisitorType VisitorType_MIN = unknown;
constexpr VisitorType VisitorType_MAX = subscriber;
constexpr int VisitorType_ARRAYSIZE = VisitorType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* VisitorType_descriptor();
template<typename T>
inline const std::string& VisitorType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, VisitorType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function VisitorType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    VisitorType_descriptor(), enum_t_value);
}
inline bool VisitorType_Parse(
    const std::string& name, VisitorType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<VisitorType>(
    VisitorType_descriptor(), name, value);
}
// ===================================================================

class VisitorProperty :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.VisitorProperty) */ {
 public:
  VisitorProperty();
  virtual ~VisitorProperty();

  VisitorProperty(const VisitorProperty& from);
  VisitorProperty(VisitorProperty&& from) noexcept
    : VisitorProperty() {
    *this = ::std::move(from);
  }

  inline VisitorProperty& operator=(const VisitorProperty& from) {
    CopyFrom(from);
    return *this;
  }
  inline VisitorProperty& operator=(VisitorProperty&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const VisitorProperty& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const VisitorProperty* internal_default_instance() {
    return reinterpret_cast<const VisitorProperty*>(
               &_VisitorProperty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(VisitorProperty& a, VisitorProperty& b) {
    a.Swap(&b);
  }
  inline void Swap(VisitorProperty* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline VisitorProperty* New() const final {
    return CreateMaybeMessage<VisitorProperty>(nullptr);
  }

  VisitorProperty* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<VisitorProperty>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const VisitorProperty& from);
  void MergeFrom(const VisitorProperty& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(VisitorProperty* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.VisitorProperty";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_customized_5fmessage_2eproto);
    return ::descriptor_table_customized_5fmessage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCategoryFieldNumber = 2,
    kTopicFieldNumber = 3,
    kExtensionFieldNumber = 4,
    kTypeFieldNumber = 1,
  };
  // string category = 2;
  void clear_category();
  const std::string& category() const;
  void set_category(const std::string& value);
  void set_category(std::string&& value);
  void set_category(const char* value);
  void set_category(const char* value, size_t size);
  std::string* mutable_category();
  std::string* release_category();
  void set_allocated_category(std::string* category);
  private:
  const std::string& _internal_category() const;
  void _internal_set_category(const std::string& value);
  std::string* _internal_mutable_category();
  public:

  // string topic = 3;
  void clear_topic();
  const std::string& topic() const;
  void set_topic(const std::string& value);
  void set_topic(std::string&& value);
  void set_topic(const char* value);
  void set_topic(const char* value, size_t size);
  std::string* mutable_topic();
  std::string* release_topic();
  void set_allocated_topic(std::string* topic);
  private:
  const std::string& _internal_topic() const;
  void _internal_set_topic(const std::string& value);
  std::string* _internal_mutable_topic();
  public:

  // string extension = 4;
  void clear_extension();
  const std::string& extension() const;
  void set_extension(const std::string& value);
  void set_extension(std::string&& value);
  void set_extension(const char* value);
  void set_extension(const char* value, size_t size);
  std::string* mutable_extension();
  std::string* release_extension();
  void set_allocated_extension(std::string* extension);
  private:
  const std::string& _internal_extension() const;
  void _internal_set_extension(const std::string& value);
  std::string* _internal_mutable_extension();
  public:

  // .message.VisitorType type = 1;
  void clear_type();
  ::message::VisitorType type() const;
  void set_type(::message::VisitorType value);
  private:
  ::message::VisitorType _internal_type() const;
  void _internal_set_type(::message::VisitorType value);
  public:

  // @@protoc_insertion_point(class_scope:message.VisitorProperty)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr category_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr topic_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr extension_;
  int type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_customized_5fmessage_2eproto;
};
// -------------------------------------------------------------------

class PublisherMessage :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.PublisherMessage) */ {
 public:
  PublisherMessage();
  virtual ~PublisherMessage();

  PublisherMessage(const PublisherMessage& from);
  PublisherMessage(PublisherMessage&& from) noexcept
    : PublisherMessage() {
    *this = ::std::move(from);
  }

  inline PublisherMessage& operator=(const PublisherMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline PublisherMessage& operator=(PublisherMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const PublisherMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PublisherMessage* internal_default_instance() {
    return reinterpret_cast<const PublisherMessage*>(
               &_PublisherMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PublisherMessage& a, PublisherMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(PublisherMessage* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PublisherMessage* New() const final {
    return CreateMaybeMessage<PublisherMessage>(nullptr);
  }

  PublisherMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PublisherMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PublisherMessage& from);
  void MergeFrom(const PublisherMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PublisherMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.PublisherMessage";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_customized_5fmessage_2eproto);
    return ::descriptor_table_customized_5fmessage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPayloadFieldNumber = 2,
    kPropertiesFieldNumber = 1,
  };
  // string payload = 2;
  void clear_payload();
  const std::string& payload() const;
  void set_payload(const std::string& value);
  void set_payload(std::string&& value);
  void set_payload(const char* value);
  void set_payload(const char* value, size_t size);
  std::string* mutable_payload();
  std::string* release_payload();
  void set_allocated_payload(std::string* payload);
  private:
  const std::string& _internal_payload() const;
  void _internal_set_payload(const std::string& value);
  std::string* _internal_mutable_payload();
  public:

  // .message.VisitorProperty properties = 1;
  bool has_properties() const;
  private:
  bool _internal_has_properties() const;
  public:
  void clear_properties();
  const ::message::VisitorProperty& properties() const;
  ::message::VisitorProperty* release_properties();
  ::message::VisitorProperty* mutable_properties();
  void set_allocated_properties(::message::VisitorProperty* properties);
  private:
  const ::message::VisitorProperty& _internal_properties() const;
  ::message::VisitorProperty* _internal_mutable_properties();
  public:

  // @@protoc_insertion_point(class_scope:message.PublisherMessage)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr payload_;
  ::message::VisitorProperty* properties_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_customized_5fmessage_2eproto;
};
// -------------------------------------------------------------------

class SubscriberMessage :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:message.SubscriberMessage) */ {
 public:
  SubscriberMessage();
  virtual ~SubscriberMessage();

  SubscriberMessage(const SubscriberMessage& from);
  SubscriberMessage(SubscriberMessage&& from) noexcept
    : SubscriberMessage() {
    *this = ::std::move(from);
  }

  inline SubscriberMessage& operator=(const SubscriberMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline SubscriberMessage& operator=(SubscriberMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SubscriberMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SubscriberMessage* internal_default_instance() {
    return reinterpret_cast<const SubscriberMessage*>(
               &_SubscriberMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(SubscriberMessage& a, SubscriberMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(SubscriberMessage* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SubscriberMessage* New() const final {
    return CreateMaybeMessage<SubscriberMessage>(nullptr);
  }

  SubscriberMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SubscriberMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SubscriberMessage& from);
  void MergeFrom(const SubscriberMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SubscriberMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "message.SubscriberMessage";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_customized_5fmessage_2eproto);
    return ::descriptor_table_customized_5fmessage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPropertiesFieldNumber = 1,
  };
  // .message.VisitorProperty properties = 1;
  bool has_properties() const;
  private:
  bool _internal_has_properties() const;
  public:
  void clear_properties();
  const ::message::VisitorProperty& properties() const;
  ::message::VisitorProperty* release_properties();
  ::message::VisitorProperty* mutable_properties();
  void set_allocated_properties(::message::VisitorProperty* properties);
  private:
  const ::message::VisitorProperty& _internal_properties() const;
  ::message::VisitorProperty* _internal_mutable_properties();
  public:

  // @@protoc_insertion_point(class_scope:message.SubscriberMessage)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::message::VisitorProperty* properties_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_customized_5fmessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// VisitorProperty

// .message.VisitorType type = 1;
inline void VisitorProperty::clear_type() {
  type_ = 0;
}
inline ::message::VisitorType VisitorProperty::_internal_type() const {
  return static_cast< ::message::VisitorType >(type_);
}
inline ::message::VisitorType VisitorProperty::type() const {
  // @@protoc_insertion_point(field_get:message.VisitorProperty.type)
  return _internal_type();
}
inline void VisitorProperty::_internal_set_type(::message::VisitorType value) {
  
  type_ = value;
}
inline void VisitorProperty::set_type(::message::VisitorType value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:message.VisitorProperty.type)
}

// string category = 2;
inline void VisitorProperty::clear_category() {
  category_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& VisitorProperty::category() const {
  // @@protoc_insertion_point(field_get:message.VisitorProperty.category)
  return _internal_category();
}
inline void VisitorProperty::set_category(const std::string& value) {
  _internal_set_category(value);
  // @@protoc_insertion_point(field_set:message.VisitorProperty.category)
}
inline std::string* VisitorProperty::mutable_category() {
  // @@protoc_insertion_point(field_mutable:message.VisitorProperty.category)
  return _internal_mutable_category();
}
inline const std::string& VisitorProperty::_internal_category() const {
  return category_.GetNoArena();
}
inline void VisitorProperty::_internal_set_category(const std::string& value) {
  
  category_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void VisitorProperty::set_category(std::string&& value) {
  
  category_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.VisitorProperty.category)
}
inline void VisitorProperty::set_category(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  category_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.VisitorProperty.category)
}
inline void VisitorProperty::set_category(const char* value, size_t size) {
  
  category_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.VisitorProperty.category)
}
inline std::string* VisitorProperty::_internal_mutable_category() {
  
  return category_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* VisitorProperty::release_category() {
  // @@protoc_insertion_point(field_release:message.VisitorProperty.category)
  
  return category_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void VisitorProperty::set_allocated_category(std::string* category) {
  if (category != nullptr) {
    
  } else {
    
  }
  category_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), category);
  // @@protoc_insertion_point(field_set_allocated:message.VisitorProperty.category)
}

// string topic = 3;
inline void VisitorProperty::clear_topic() {
  topic_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& VisitorProperty::topic() const {
  // @@protoc_insertion_point(field_get:message.VisitorProperty.topic)
  return _internal_topic();
}
inline void VisitorProperty::set_topic(const std::string& value) {
  _internal_set_topic(value);
  // @@protoc_insertion_point(field_set:message.VisitorProperty.topic)
}
inline std::string* VisitorProperty::mutable_topic() {
  // @@protoc_insertion_point(field_mutable:message.VisitorProperty.topic)
  return _internal_mutable_topic();
}
inline const std::string& VisitorProperty::_internal_topic() const {
  return topic_.GetNoArena();
}
inline void VisitorProperty::_internal_set_topic(const std::string& value) {
  
  topic_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void VisitorProperty::set_topic(std::string&& value) {
  
  topic_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.VisitorProperty.topic)
}
inline void VisitorProperty::set_topic(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  topic_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.VisitorProperty.topic)
}
inline void VisitorProperty::set_topic(const char* value, size_t size) {
  
  topic_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.VisitorProperty.topic)
}
inline std::string* VisitorProperty::_internal_mutable_topic() {
  
  return topic_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* VisitorProperty::release_topic() {
  // @@protoc_insertion_point(field_release:message.VisitorProperty.topic)
  
  return topic_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void VisitorProperty::set_allocated_topic(std::string* topic) {
  if (topic != nullptr) {
    
  } else {
    
  }
  topic_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), topic);
  // @@protoc_insertion_point(field_set_allocated:message.VisitorProperty.topic)
}

// string extension = 4;
inline void VisitorProperty::clear_extension() {
  extension_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& VisitorProperty::extension() const {
  // @@protoc_insertion_point(field_get:message.VisitorProperty.extension)
  return _internal_extension();
}
inline void VisitorProperty::set_extension(const std::string& value) {
  _internal_set_extension(value);
  // @@protoc_insertion_point(field_set:message.VisitorProperty.extension)
}
inline std::string* VisitorProperty::mutable_extension() {
  // @@protoc_insertion_point(field_mutable:message.VisitorProperty.extension)
  return _internal_mutable_extension();
}
inline const std::string& VisitorProperty::_internal_extension() const {
  return extension_.GetNoArena();
}
inline void VisitorProperty::_internal_set_extension(const std::string& value) {
  
  extension_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void VisitorProperty::set_extension(std::string&& value) {
  
  extension_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.VisitorProperty.extension)
}
inline void VisitorProperty::set_extension(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  extension_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.VisitorProperty.extension)
}
inline void VisitorProperty::set_extension(const char* value, size_t size) {
  
  extension_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.VisitorProperty.extension)
}
inline std::string* VisitorProperty::_internal_mutable_extension() {
  
  return extension_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* VisitorProperty::release_extension() {
  // @@protoc_insertion_point(field_release:message.VisitorProperty.extension)
  
  return extension_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void VisitorProperty::set_allocated_extension(std::string* extension) {
  if (extension != nullptr) {
    
  } else {
    
  }
  extension_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), extension);
  // @@protoc_insertion_point(field_set_allocated:message.VisitorProperty.extension)
}

// -------------------------------------------------------------------

// PublisherMessage

// .message.VisitorProperty properties = 1;
inline bool PublisherMessage::_internal_has_properties() const {
  return this != internal_default_instance() && properties_ != nullptr;
}
inline bool PublisherMessage::has_properties() const {
  return _internal_has_properties();
}
inline void PublisherMessage::clear_properties() {
  if (GetArenaNoVirtual() == nullptr && properties_ != nullptr) {
    delete properties_;
  }
  properties_ = nullptr;
}
inline const ::message::VisitorProperty& PublisherMessage::_internal_properties() const {
  const ::message::VisitorProperty* p = properties_;
  return p != nullptr ? *p : *reinterpret_cast<const ::message::VisitorProperty*>(
      &::message::_VisitorProperty_default_instance_);
}
inline const ::message::VisitorProperty& PublisherMessage::properties() const {
  // @@protoc_insertion_point(field_get:message.PublisherMessage.properties)
  return _internal_properties();
}
inline ::message::VisitorProperty* PublisherMessage::release_properties() {
  // @@protoc_insertion_point(field_release:message.PublisherMessage.properties)
  
  ::message::VisitorProperty* temp = properties_;
  properties_ = nullptr;
  return temp;
}
inline ::message::VisitorProperty* PublisherMessage::_internal_mutable_properties() {
  
  if (properties_ == nullptr) {
    auto* p = CreateMaybeMessage<::message::VisitorProperty>(GetArenaNoVirtual());
    properties_ = p;
  }
  return properties_;
}
inline ::message::VisitorProperty* PublisherMessage::mutable_properties() {
  // @@protoc_insertion_point(field_mutable:message.PublisherMessage.properties)
  return _internal_mutable_properties();
}
inline void PublisherMessage::set_allocated_properties(::message::VisitorProperty* properties) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete properties_;
  }
  if (properties) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      properties = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, properties, submessage_arena);
    }
    
  } else {
    
  }
  properties_ = properties;
  // @@protoc_insertion_point(field_set_allocated:message.PublisherMessage.properties)
}

// string payload = 2;
inline void PublisherMessage::clear_payload() {
  payload_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& PublisherMessage::payload() const {
  // @@protoc_insertion_point(field_get:message.PublisherMessage.payload)
  return _internal_payload();
}
inline void PublisherMessage::set_payload(const std::string& value) {
  _internal_set_payload(value);
  // @@protoc_insertion_point(field_set:message.PublisherMessage.payload)
}
inline std::string* PublisherMessage::mutable_payload() {
  // @@protoc_insertion_point(field_mutable:message.PublisherMessage.payload)
  return _internal_mutable_payload();
}
inline const std::string& PublisherMessage::_internal_payload() const {
  return payload_.GetNoArena();
}
inline void PublisherMessage::_internal_set_payload(const std::string& value) {
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void PublisherMessage::set_payload(std::string&& value) {
  
  payload_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:message.PublisherMessage.payload)
}
inline void PublisherMessage::set_payload(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:message.PublisherMessage.payload)
}
inline void PublisherMessage::set_payload(const char* value, size_t size) {
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:message.PublisherMessage.payload)
}
inline std::string* PublisherMessage::_internal_mutable_payload() {
  
  return payload_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* PublisherMessage::release_payload() {
  // @@protoc_insertion_point(field_release:message.PublisherMessage.payload)
  
  return payload_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void PublisherMessage::set_allocated_payload(std::string* payload) {
  if (payload != nullptr) {
    
  } else {
    
  }
  payload_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:message.PublisherMessage.payload)
}

// -------------------------------------------------------------------

// SubscriberMessage

// .message.VisitorProperty properties = 1;
inline bool SubscriberMessage::_internal_has_properties() const {
  return this != internal_default_instance() && properties_ != nullptr;
}
inline bool SubscriberMessage::has_properties() const {
  return _internal_has_properties();
}
inline void SubscriberMessage::clear_properties() {
  if (GetArenaNoVirtual() == nullptr && properties_ != nullptr) {
    delete properties_;
  }
  properties_ = nullptr;
}
inline const ::message::VisitorProperty& SubscriberMessage::_internal_properties() const {
  const ::message::VisitorProperty* p = properties_;
  return p != nullptr ? *p : *reinterpret_cast<const ::message::VisitorProperty*>(
      &::message::_VisitorProperty_default_instance_);
}
inline const ::message::VisitorProperty& SubscriberMessage::properties() const {
  // @@protoc_insertion_point(field_get:message.SubscriberMessage.properties)
  return _internal_properties();
}
inline ::message::VisitorProperty* SubscriberMessage::release_properties() {
  // @@protoc_insertion_point(field_release:message.SubscriberMessage.properties)
  
  ::message::VisitorProperty* temp = properties_;
  properties_ = nullptr;
  return temp;
}
inline ::message::VisitorProperty* SubscriberMessage::_internal_mutable_properties() {
  
  if (properties_ == nullptr) {
    auto* p = CreateMaybeMessage<::message::VisitorProperty>(GetArenaNoVirtual());
    properties_ = p;
  }
  return properties_;
}
inline ::message::VisitorProperty* SubscriberMessage::mutable_properties() {
  // @@protoc_insertion_point(field_mutable:message.SubscriberMessage.properties)
  return _internal_mutable_properties();
}
inline void SubscriberMessage::set_allocated_properties(::message::VisitorProperty* properties) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete properties_;
  }
  if (properties) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      properties = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, properties, submessage_arena);
    }
    
  } else {
    
  }
  properties_ = properties;
  // @@protoc_insertion_point(field_set_allocated:message.SubscriberMessage.properties)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::message::VisitorType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::VisitorType>() {
  return ::message::VisitorType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_customized_5fmessage_2eproto
