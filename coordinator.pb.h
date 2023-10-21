// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: coordinator.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_coordinator_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_coordinator_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023004 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_bases.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
#include "google/protobuf/timestamp.pb.h"
#include "google/protobuf/empty.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_coordinator_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_coordinator_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_coordinator_2eproto;
namespace csce438 {
class Confirmation;
struct ConfirmationDefaultTypeInternal;
extern ConfirmationDefaultTypeInternal _Confirmation_default_instance_;
class ID;
struct IDDefaultTypeInternal;
extern IDDefaultTypeInternal _ID_default_instance_;
class Path;
struct PathDefaultTypeInternal;
extern PathDefaultTypeInternal _Path_default_instance_;
class PathAndData;
struct PathAndDataDefaultTypeInternal;
extern PathAndDataDefaultTypeInternal _PathAndData_default_instance_;
class ServerInfo;
struct ServerInfoDefaultTypeInternal;
extern ServerInfoDefaultTypeInternal _ServerInfo_default_instance_;
}  // namespace csce438
PROTOBUF_NAMESPACE_OPEN
template <>
::csce438::Confirmation* Arena::CreateMaybeMessage<::csce438::Confirmation>(Arena*);
template <>
::csce438::ID* Arena::CreateMaybeMessage<::csce438::ID>(Arena*);
template <>
::csce438::Path* Arena::CreateMaybeMessage<::csce438::Path>(Arena*);
template <>
::csce438::PathAndData* Arena::CreateMaybeMessage<::csce438::PathAndData>(Arena*);
template <>
::csce438::ServerInfo* Arena::CreateMaybeMessage<::csce438::ServerInfo>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace csce438 {

// ===================================================================


// -------------------------------------------------------------------

class ServerInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:csce438.ServerInfo) */ {
 public:
  inline ServerInfo() : ServerInfo(nullptr) {}
  ~ServerInfo() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR ServerInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ServerInfo(const ServerInfo& from);
  ServerInfo(ServerInfo&& from) noexcept
    : ServerInfo() {
    *this = ::std::move(from);
  }

  inline ServerInfo& operator=(const ServerInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline ServerInfo& operator=(ServerInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ServerInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const ServerInfo* internal_default_instance() {
    return reinterpret_cast<const ServerInfo*>(
               &_ServerInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ServerInfo& a, ServerInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(ServerInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ServerInfo* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ServerInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ServerInfo>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ServerInfo& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ServerInfo& from) {
    ServerInfo::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ServerInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "csce438.ServerInfo";
  }
  protected:
  explicit ServerInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kHostnameFieldNumber = 2,
    kPortFieldNumber = 3,
    kTypeFieldNumber = 4,
    kClusterIDFieldNumber = 5,
    kServerIDFieldNumber = 1,
  };
  // string hostname = 2;
  void clear_hostname() ;
  const std::string& hostname() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_hostname(Arg_&& arg, Args_... args);
  std::string* mutable_hostname();
  PROTOBUF_NODISCARD std::string* release_hostname();
  void set_allocated_hostname(std::string* ptr);

  private:
  const std::string& _internal_hostname() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_hostname(
      const std::string& value);
  std::string* _internal_mutable_hostname();

  public:
  // string port = 3;
  void clear_port() ;
  const std::string& port() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_port(Arg_&& arg, Args_... args);
  std::string* mutable_port();
  PROTOBUF_NODISCARD std::string* release_port();
  void set_allocated_port(std::string* ptr);

  private:
  const std::string& _internal_port() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_port(
      const std::string& value);
  std::string* _internal_mutable_port();

  public:
  // string type = 4;
  void clear_type() ;
  const std::string& type() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_type(Arg_&& arg, Args_... args);
  std::string* mutable_type();
  PROTOBUF_NODISCARD std::string* release_type();
  void set_allocated_type(std::string* ptr);

  private:
  const std::string& _internal_type() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_type(
      const std::string& value);
  std::string* _internal_mutable_type();

  public:
  // string clusterID = 5;
  void clear_clusterid() ;
  const std::string& clusterid() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_clusterid(Arg_&& arg, Args_... args);
  std::string* mutable_clusterid();
  PROTOBUF_NODISCARD std::string* release_clusterid();
  void set_allocated_clusterid(std::string* ptr);

  private:
  const std::string& _internal_clusterid() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_clusterid(
      const std::string& value);
  std::string* _internal_mutable_clusterid();

  public:
  // int32 serverID = 1;
  void clear_serverid() ;
  ::int32_t serverid() const;
  void set_serverid(::int32_t value);

  private:
  ::int32_t _internal_serverid() const;
  void _internal_set_serverid(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:csce438.ServerInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr hostname_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr port_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr type_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr clusterid_;
    ::int32_t serverid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_coordinator_2eproto;
};// -------------------------------------------------------------------

class Confirmation final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:csce438.Confirmation) */ {
 public:
  inline Confirmation() : Confirmation(nullptr) {}
  ~Confirmation() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Confirmation(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Confirmation(const Confirmation& from);
  Confirmation(Confirmation&& from) noexcept
    : Confirmation() {
    *this = ::std::move(from);
  }

  inline Confirmation& operator=(const Confirmation& from) {
    CopyFrom(from);
    return *this;
  }
  inline Confirmation& operator=(Confirmation&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Confirmation& default_instance() {
    return *internal_default_instance();
  }
  static inline const Confirmation* internal_default_instance() {
    return reinterpret_cast<const Confirmation*>(
               &_Confirmation_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Confirmation& a, Confirmation& b) {
    a.Swap(&b);
  }
  inline void Swap(Confirmation* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Confirmation* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Confirmation* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Confirmation>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Confirmation& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Confirmation& from) {
    Confirmation::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Confirmation* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "csce438.Confirmation";
  }
  protected:
  explicit Confirmation(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kStatusFieldNumber = 1,
  };
  // bool status = 1;
  void clear_status() ;
  bool status() const;
  void set_status(bool value);

  private:
  bool _internal_status() const;
  void _internal_set_status(bool value);

  public:
  // @@protoc_insertion_point(class_scope:csce438.Confirmation)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool status_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_coordinator_2eproto;
};// -------------------------------------------------------------------

class ID final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:csce438.ID) */ {
 public:
  inline ID() : ID(nullptr) {}
  ~ID() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR ID(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ID(const ID& from);
  ID(ID&& from) noexcept
    : ID() {
    *this = ::std::move(from);
  }

  inline ID& operator=(const ID& from) {
    CopyFrom(from);
    return *this;
  }
  inline ID& operator=(ID&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ID& default_instance() {
    return *internal_default_instance();
  }
  static inline const ID* internal_default_instance() {
    return reinterpret_cast<const ID*>(
               &_ID_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(ID& a, ID& b) {
    a.Swap(&b);
  }
  inline void Swap(ID* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ID* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ID* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ID>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ID& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ID& from) {
    ID::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ID* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "csce438.ID";
  }
  protected:
  explicit ID(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // int32 id = 1;
  void clear_id() ;
  ::int32_t id() const;
  void set_id(::int32_t value);

  private:
  ::int32_t _internal_id() const;
  void _internal_set_id(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:csce438.ID)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::int32_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_coordinator_2eproto;
};// -------------------------------------------------------------------

class Path final :
    public ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase /* @@protoc_insertion_point(class_definition:csce438.Path) */ {
 public:
  inline Path() : Path(nullptr) {}
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Path(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Path(const Path& from);
  Path(Path&& from) noexcept
    : Path() {
    *this = ::std::move(from);
  }

  inline Path& operator=(const Path& from) {
    CopyFrom(from);
    return *this;
  }
  inline Path& operator=(Path&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Path& default_instance() {
    return *internal_default_instance();
  }
  static inline const Path* internal_default_instance() {
    return reinterpret_cast<const Path*>(
               &_Path_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(Path& a, Path& b) {
    a.Swap(&b);
  }
  inline void Swap(Path* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Path* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Path* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Path>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const Path& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const Path& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }
  public:

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "csce438.Path";
  }
  protected:
  explicit Path(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:csce438.Path)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
  };
  friend struct ::TableStruct_coordinator_2eproto;
};// -------------------------------------------------------------------

class PathAndData final :
    public ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase /* @@protoc_insertion_point(class_definition:csce438.PathAndData) */ {
 public:
  inline PathAndData() : PathAndData(nullptr) {}
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR PathAndData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PathAndData(const PathAndData& from);
  PathAndData(PathAndData&& from) noexcept
    : PathAndData() {
    *this = ::std::move(from);
  }

  inline PathAndData& operator=(const PathAndData& from) {
    CopyFrom(from);
    return *this;
  }
  inline PathAndData& operator=(PathAndData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PathAndData& default_instance() {
    return *internal_default_instance();
  }
  static inline const PathAndData* internal_default_instance() {
    return reinterpret_cast<const PathAndData*>(
               &_PathAndData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  friend void swap(PathAndData& a, PathAndData& b) {
    a.Swap(&b);
  }
  inline void Swap(PathAndData* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PathAndData* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PathAndData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PathAndData>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const PathAndData& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const PathAndData& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }
  public:

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "csce438.PathAndData";
  }
  protected:
  explicit PathAndData(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:csce438.PathAndData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
  };
  friend struct ::TableStruct_coordinator_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ServerInfo

// int32 serverID = 1;
inline void ServerInfo::clear_serverid() {
  _impl_.serverid_ = 0;
}
inline ::int32_t ServerInfo::serverid() const {
  // @@protoc_insertion_point(field_get:csce438.ServerInfo.serverID)
  return _internal_serverid();
}
inline void ServerInfo::set_serverid(::int32_t value) {
  _internal_set_serverid(value);
  // @@protoc_insertion_point(field_set:csce438.ServerInfo.serverID)
}
inline ::int32_t ServerInfo::_internal_serverid() const {
  return _impl_.serverid_;
}
inline void ServerInfo::_internal_set_serverid(::int32_t value) {
  ;
  _impl_.serverid_ = value;
}

// string hostname = 2;
inline void ServerInfo::clear_hostname() {
  _impl_.hostname_.ClearToEmpty();
}
inline const std::string& ServerInfo::hostname() const {
  // @@protoc_insertion_point(field_get:csce438.ServerInfo.hostname)
  return _internal_hostname();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ServerInfo::set_hostname(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.hostname_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:csce438.ServerInfo.hostname)
}
inline std::string* ServerInfo::mutable_hostname() {
  std::string* _s = _internal_mutable_hostname();
  // @@protoc_insertion_point(field_mutable:csce438.ServerInfo.hostname)
  return _s;
}
inline const std::string& ServerInfo::_internal_hostname() const {
  return _impl_.hostname_.Get();
}
inline void ServerInfo::_internal_set_hostname(const std::string& value) {
  ;


  _impl_.hostname_.Set(value, GetArenaForAllocation());
}
inline std::string* ServerInfo::_internal_mutable_hostname() {
  ;
  return _impl_.hostname_.Mutable( GetArenaForAllocation());
}
inline std::string* ServerInfo::release_hostname() {
  // @@protoc_insertion_point(field_release:csce438.ServerInfo.hostname)
  return _impl_.hostname_.Release();
}
inline void ServerInfo::set_allocated_hostname(std::string* value) {
  _impl_.hostname_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.hostname_.IsDefault()) {
          _impl_.hostname_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:csce438.ServerInfo.hostname)
}

// string port = 3;
inline void ServerInfo::clear_port() {
  _impl_.port_.ClearToEmpty();
}
inline const std::string& ServerInfo::port() const {
  // @@protoc_insertion_point(field_get:csce438.ServerInfo.port)
  return _internal_port();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ServerInfo::set_port(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.port_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:csce438.ServerInfo.port)
}
inline std::string* ServerInfo::mutable_port() {
  std::string* _s = _internal_mutable_port();
  // @@protoc_insertion_point(field_mutable:csce438.ServerInfo.port)
  return _s;
}
inline const std::string& ServerInfo::_internal_port() const {
  return _impl_.port_.Get();
}
inline void ServerInfo::_internal_set_port(const std::string& value) {
  ;


  _impl_.port_.Set(value, GetArenaForAllocation());
}
inline std::string* ServerInfo::_internal_mutable_port() {
  ;
  return _impl_.port_.Mutable( GetArenaForAllocation());
}
inline std::string* ServerInfo::release_port() {
  // @@protoc_insertion_point(field_release:csce438.ServerInfo.port)
  return _impl_.port_.Release();
}
inline void ServerInfo::set_allocated_port(std::string* value) {
  _impl_.port_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.port_.IsDefault()) {
          _impl_.port_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:csce438.ServerInfo.port)
}

// string type = 4;
inline void ServerInfo::clear_type() {
  _impl_.type_.ClearToEmpty();
}
inline const std::string& ServerInfo::type() const {
  // @@protoc_insertion_point(field_get:csce438.ServerInfo.type)
  return _internal_type();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ServerInfo::set_type(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.type_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:csce438.ServerInfo.type)
}
inline std::string* ServerInfo::mutable_type() {
  std::string* _s = _internal_mutable_type();
  // @@protoc_insertion_point(field_mutable:csce438.ServerInfo.type)
  return _s;
}
inline const std::string& ServerInfo::_internal_type() const {
  return _impl_.type_.Get();
}
inline void ServerInfo::_internal_set_type(const std::string& value) {
  ;


  _impl_.type_.Set(value, GetArenaForAllocation());
}
inline std::string* ServerInfo::_internal_mutable_type() {
  ;
  return _impl_.type_.Mutable( GetArenaForAllocation());
}
inline std::string* ServerInfo::release_type() {
  // @@protoc_insertion_point(field_release:csce438.ServerInfo.type)
  return _impl_.type_.Release();
}
inline void ServerInfo::set_allocated_type(std::string* value) {
  _impl_.type_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.type_.IsDefault()) {
          _impl_.type_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:csce438.ServerInfo.type)
}

// string clusterID = 5;
inline void ServerInfo::clear_clusterid() {
  _impl_.clusterid_.ClearToEmpty();
}
inline const std::string& ServerInfo::clusterid() const {
  // @@protoc_insertion_point(field_get:csce438.ServerInfo.clusterID)
  return _internal_clusterid();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ServerInfo::set_clusterid(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.clusterid_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:csce438.ServerInfo.clusterID)
}
inline std::string* ServerInfo::mutable_clusterid() {
  std::string* _s = _internal_mutable_clusterid();
  // @@protoc_insertion_point(field_mutable:csce438.ServerInfo.clusterID)
  return _s;
}
inline const std::string& ServerInfo::_internal_clusterid() const {
  return _impl_.clusterid_.Get();
}
inline void ServerInfo::_internal_set_clusterid(const std::string& value) {
  ;


  _impl_.clusterid_.Set(value, GetArenaForAllocation());
}
inline std::string* ServerInfo::_internal_mutable_clusterid() {
  ;
  return _impl_.clusterid_.Mutable( GetArenaForAllocation());
}
inline std::string* ServerInfo::release_clusterid() {
  // @@protoc_insertion_point(field_release:csce438.ServerInfo.clusterID)
  return _impl_.clusterid_.Release();
}
inline void ServerInfo::set_allocated_clusterid(std::string* value) {
  _impl_.clusterid_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.clusterid_.IsDefault()) {
          _impl_.clusterid_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:csce438.ServerInfo.clusterID)
}

// -------------------------------------------------------------------

// Confirmation

// bool status = 1;
inline void Confirmation::clear_status() {
  _impl_.status_ = false;
}
inline bool Confirmation::status() const {
  // @@protoc_insertion_point(field_get:csce438.Confirmation.status)
  return _internal_status();
}
inline void Confirmation::set_status(bool value) {
  _internal_set_status(value);
  // @@protoc_insertion_point(field_set:csce438.Confirmation.status)
}
inline bool Confirmation::_internal_status() const {
  return _impl_.status_;
}
inline void Confirmation::_internal_set_status(bool value) {
  ;
  _impl_.status_ = value;
}

// -------------------------------------------------------------------

// ID

// int32 id = 1;
inline void ID::clear_id() {
  _impl_.id_ = 0;
}
inline ::int32_t ID::id() const {
  // @@protoc_insertion_point(field_get:csce438.ID.id)
  return _internal_id();
}
inline void ID::set_id(::int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:csce438.ID.id)
}
inline ::int32_t ID::_internal_id() const {
  return _impl_.id_;
}
inline void ID::_internal_set_id(::int32_t value) {
  ;
  _impl_.id_ = value;
}

// -------------------------------------------------------------------

// Path

// -------------------------------------------------------------------

// PathAndData

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace csce438


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_coordinator_2eproto_2epb_2eh
