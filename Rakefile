# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/extensiontask"

task build: :compile

Rake::ExtensionTask.new("ooxml_crypt") do |ext|
  ext.name    = "native"
  ext.lib_dir = "lib/ooxml_crypt"
end

task default: %i[clobber compile]