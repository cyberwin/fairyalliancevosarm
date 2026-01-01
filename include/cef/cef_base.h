#ifndef CEF_BASE_H_
#define CEF_BASE_H_

#include <atomic>
#include <memory>

namespace Cef {
class RefCountedBase {
 private:
  mutable std::atomic<int> ref_count_ = {0};

 public:
  void AddRef() const { ref_count_.fetch_add(1, std::memory_order_relaxed); }

  bool Release() const {
    int count = ref_count_.fetch_sub(1, std::memory_order_acq_rel) - 1;
    if (count == 0) {
      delete this;
      return true;
    }
    return false;
  }

  int GetRefCt() const { return ref_count_.load(std::memory_order_relaxed); }

 protected:
  RefCountedBase() = default;
  virtual ~RefCountedBase() = default;

 private:
  RefCountedBase(const RefCountedBase&) = delete;
  RefCountedBase& operator=(const RefCountedBase&) = delete;
};

template <typename T>
class RefPtr {
 public:
  RefPtr() : ptr_(nullptr) {}

  explicit RefPtr(T* ptr) : ptr_(ptr) {
    if (ptr_) ptr_->AddRef();
  }

  RefPtr(const RefPtr& other) : ptr_(other.ptr_) {
    if (ptr_) ptr_->AddRef();
  }

  ~RefPtr() {
    if (ptr_) ptr_->Release();
  }

  RefPtr& operator=(const RefPtr& other) {
    if (ptr_ != other.ptr_) {
      T* old_ptr = ptr_;
      ptr_ = other.ptr_;
      if (ptr_) ptr_->AddRef();
      if (old_ptr) old_ptr->Release();
    }
    return *this;
  }

  T* get() const { return ptr_; }
  T* operator->() const { return ptr_; }
  T& operator*() const { return *ptr_; }
  operator bool() const { return ptr_ != nullptr; }

 private:
  T* ptr_;
};
}  // namespace Cef

#define IMPLEMENT_REFCOUNTING(cls) \
  void AddRef() const override { Cef::RefCountedBase::AddRef(); } \
  bool Release() const override { return Cef::RefCountedBase::Release(); } \
  int GetRefCt() const override { return Cef::RefCountedBase::GetRefCt(); }

#define REFCOUNTING_METHODS \
  virtual void AddRef() const = 0; \
  virtual bool Release() const = 0; \
  virtual int GetRefCt() const = 0;

#endif  // CEF_BASE_H_
