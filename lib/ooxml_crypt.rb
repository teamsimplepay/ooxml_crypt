# frozen_string_literal: true

require_relative "ooxml_crypt/version"

require "tempfile"
require "ooxml_crypt/native"

module OoxmlCrypt
  class Error < StandardError; end
  class FileNotFound < Error; end
  class EmptyPassword < Error; end

  ERRORS = { # should be kept in sync with msoc.h
    1  => "not supported format",
    2  => "already encrypted",
    3  => "already decrypted",
    4  => "bad password",
    5  => "bad parameter",
    6  => "small max size",
    7  => "no memory",
    8  => "internal exception",
    9  => "too large file",
    10 => "inFile is empty",
    11 => "outFile is empty",
    12 => "password is empty",
  }

  def self.encrypt_file(input, password, output)
    raise EmptyPassword if password.nil? || password.empty?
    raise FileNotFound, input unless File.exist?(input)

    result = Native.encrypt_file(input, password, output)
    raise Error, ERRORS[-result] if result != 0
  end

  def self.decrypt_file(input, password, output)
    raise EmptyPassword if password.nil? || password.empty?
    raise FileNotFound, input unless File.exist?(input)

    result = Native.decrypt_file(input, password, output)
    raise Error, ERRORS[-result] if result != 0
  end

  def self.encrypt(data, password)
    with_temp_files(data) do |input, output|
      encrypt_file(input, password, output)
    end
  end

  def self.decrypt(data, password)
    with_temp_files(data) do |input, output|
      decrypt_file(input, password, output)
    end
  end

  private

  def self.with_temp_files(data)
    input = Tempfile.new("ooxml_crypt_input", binmode: true)
    input.write(data)
    input.close

    output = Tempfile.new("ooxml_crypt_output", binmode: true)
    output.close

    yield input.path, output.path

    result = File.binread(output.path)

    input.unlink
    output.unlink

    result
  end
end
