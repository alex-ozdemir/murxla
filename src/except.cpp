#include "except.hpp"

#include <iostream>

namespace murxla {

MessageStream::MessageStream() { stream() << "[murxla] "; }

MessageStream::MessageStream(const std::string& prefix)
{
  stream() << "[murxla] " << prefix << " ";
}

MessageStream::~MessageStream() { flush(); }

std::ostream&
MessageStream::stream()
{
  return std::cout;
}

void
MessageStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

WarnStream::WarnStream() { stream() << "murxla: WARNING: "; }

WarnStream::~WarnStream() { flush(); }

std::ostream&
WarnStream::stream()
{
  return std::cout;
}

void
WarnStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

AbortStream::AbortStream() { stream() << "murxla: ERROR: "; }

AbortStream::~AbortStream()
{
  flush();
  std::abort();
}

std::ostream&
AbortStream::stream()
{
  return std::cerr;
}

void
AbortStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

ExitStream::ExitStream(ExitCode exit_code) : d_exit(exit_code)
{
  stream() << "murxla: ERROR: ";
}

ExitStream::~ExitStream()
{
  flush();
  std::exit(d_exit);
}

std::ostream&
ExitStream::stream()
{
  return std::cerr;
}

void
ExitStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

ConfigExceptionStream::ConfigExceptionStream(
    const ConfigExceptionStream& cstream)
{
  d_ss << cstream.d_ss.rdbuf();
}

ConfigExceptionStream::~ConfigExceptionStream() noexcept(false)
{
  flush();
  throw MurxlaConfigException(d_ss);
}

std::ostream&
ConfigExceptionStream::stream()
{
  return d_ss;
}

void
ConfigExceptionStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

UntraceExceptionStream::UntraceExceptionStream(
    const UntraceExceptionStream& cstream)
{
  d_ss << cstream.d_ss.rdbuf();
}

UntraceExceptionStream::~UntraceExceptionStream() noexcept(false)
{
  flush();
  throw MurxlaActionUntraceException(d_ss);
}

std::ostream&
UntraceExceptionStream::stream()
{
  return d_ss;
}

void
UntraceExceptionStream::flush()
{
  stream() << std::endl;
  stream().flush();
}

}  // namespace murxla
