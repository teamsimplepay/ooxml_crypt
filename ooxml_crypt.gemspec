# frozen_string_literal: true

require_relative "lib/ooxml_crypt/version"

Gem::Specification.new do |spec|
  spec.name = "ooxml_crypt"
  spec.version = OoxmlCrypt::VERSION
  spec.authors = ["Ashish Kulkarni"]
  spec.email = ["ashish@kulkarni.dev"]

  spec.summary = "Library for encrypting/decrypting password-protected Microsoft Office XML (OOXML) files (e.g. .docx, .xlsx, .pptx)"
  spec.homepage = "https://github.com/teamsimplepay/ooxml_crypt"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 2.6.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = spec.homepage

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:test|spec|features)/|\.(?:git|travis|circleci)|appveyor)})
    end
  end
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/ooxml_crypt/extconf.rb"]

  spec.add_development_dependency "bundler", "~> 2.2"
  spec.add_development_dependency "rake", "~> 13.0"
  spec.add_development_dependency "rake-compiler", "~> 1.1"
end
