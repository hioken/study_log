class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :trackable, :validatable
  attachment :profile_image, destroy: false
  has_many :books
  has_many :favorites
  has_many :book_comments
  validates :name, presence: true, length: {maximum: 10, minimum: 2}
  validates :introduction, length: {maximum: 50}

  # フォロワー
    # foreign_key（FK）には、@user.xxxとした際に「@user.idがfollower_idなのかfollowed_idなのか」を指定します。
  has_many :reverse_of_relationships, class_name: 'Relationship', foreign_key: 'followed_id', dependent: :destroy
    # @user.booksのように、@user.yyyで、
    # そのユーザがフォローしている人orフォローされている人の一覧を出したい
  has_many :followers, through: :reverse_of_relationships, source: :follower

  # フォローしている人
  has_many :relationships, class_name: 'Relationship', foreign_key: "follower_id", dependent: :destroy
  has_many :followings, through: :relationships, source: :followed

  def follow(user_id)
    relationships.create(followed_id: user_id)
  end

  def unfollow(user_id)
    relationships.find_by(followed_id: user_id).destroy
  end

  def following?(user)
    followings.include?(user)
  end

  # def following?(another_user)
  #   self.followings.include?(another_user)
  # end

  # def follow(another_user)
  #   unless self == another_user
  #     self.relationships.find_or_create_by(followed_id: another_user.id)
  #   end
  # end

  # def unfollow(another_user)
  #   unless self == another_user
  #     relationship = self.relationships.find(followed_id: another_user.id)
  #     relationship.destroy if relationship
  #   end
  # end

end