#pragma once

#include <exception>

class SynaxErrorException : public std::exception {};

class NoDatabaseSelectedException : public std::exception {};

class DatabaseNoExistExcepion : public std::exception {};

class DatabaseAlreadyExistException : public std::exception {};

class TableNoExistExcepion : public std::exception {};

class TableAlreadyExistException : public std::exception {};

class IndexNoExistExcepion : public std::exception {};

class IndexAlreadyExistException : public std::exception {};

class OneIndexEachTableException : public std::exception {};

class BPlusTreeException : public std::exception {};

class IndexMustBeCreatedOnPKException : public std::exception {};

class PrimaryKeyConflictException : public std::exception {};

