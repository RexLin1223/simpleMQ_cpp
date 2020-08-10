# SimpleMQ
# Description
The libraray is using for handle unserlying socket process which made by C++ language.

# Dependency Library
We are using Boost ASIO library for implement asynchronous in network IO.
See [Boost C++ Library](https://www.boost.org/users/download/)

And we using protocol buffer to process message. See [protobuf](https://github.com/google/googletest)

# Development Platform
MSVC++ 14.0

# Role Introduction
## Broker
  - The middleware component between Publisher and Subscriber.
  - Receive message from Publisher.
  - Dispatch and deliver message to subscriber.
  - Seperate message into multiple diffirent room by topic.
## Publisher
  - Message producer.
  - Publish message and send to broker.
## Subscriber
  - Message consumer.
  - Ask to broker and register specific topic.
  
# License
MIT
